#include "IRGeneration.h"

llvm::Value* BoolLiteral::codeGen(CodeGenContext& context){
    llvm::IRBuilder<> builder(context.currentBlock());
    llvm::Module* module = context.module;
    return llvm::ConstantInt::get(llvm::Type::getInt1Ty(context.llvmContext), value ? 1 : 0);
    //1位整数1或0
}

llvm::Value* CharLiteral::codeGen(CodeGenContext& context){
    llvm::IRBuilder<> builder(context.currentBlock());
    llvm::Module* module = context.module;
    return llvm::ConstantInt::get(llvm::Type::getInt8Ty(context.llvmContext), static_cast<unsigned char>(value));
    //8位整数存储ASCII码
}

llvm::Value* IntegerLiteral::codeGen(CodeGenContext& context){
    llvm::IRBuilder<> builder(context.currentBlock());
    llvm::Module* module = context.module;
    return llvm::ConstantInt::get(llvm::Type::getInt32Ty(context.context), value);
}



llvm::Value* FunctionDec::codeGen(CodeGenContext& context){
    llvm::IRBuilder<> builder(context.currentBlock());
    llvm::Module* module = context.module;

    //返回类型type->returnType
    llvm:Type* returnType = type ? type -> codeGen(context) -> getType() : llvm::Type::getVoidTy(context.context);

    //函数参数类型parameters->paramType
    std::vector<llvm::Type*> paramTypes;
    for (const auto& param : parameters){
        auto* varDec = dynamcic_cast<VariableDec*>(param.get());
        paramTypes.push_back(varDec -> type -> getLLVMType(context));
    }

    //函数类型->funcType，创建函数
    llvm::FunctionType* funcType = llvm::FunctionType::get(returnType, paramTypes, false);
    llvm::Function* function = llvm::Function::Create(
        funcType,
        llvm::Function::ExternalLinkage, //函数在模块外可见可用于导出 or InternalLinkage函数在模块内可见（static）
        name,
        module
    );

    //参数命名，代替默认%0 %1...
    size_t index = 0;
    for (auto& arg : function -> args()) {
        arg.setName(parameters[idx++] -> name);
    }

    //生成内部结构
    if (body){
        llvm::BasicBlock* funcBlock = llvm::BasicBlock::Create(context.context, "entry", function);//基本块entry函数入口
        context.pushBlock(funcBlock);
        builder.SetInsertPoint(funcBlock);//通过IRBuilder设置插入指针
        for (auto& param : function -> args()){
            llvm::AllocaInst* alloc = buildedr.CreateAlloca(param.getType(), nullptr, param.getName());//分配内存并命名
            builder.CreateStore(&param, alloc);//CreateStore方法将对应值存储到内存里
            context.locals()[std::string(param.getName())] = alloc;//hashmap对应
        }
        body -> codeGen(context);//递归生成body部分IR

        if (!builder.GetInsertBlock() -> getTerminator()){//判断是否出现终止指令(ret)
            if(returnType -> isVoidTy()){
                builder.CreateRetVoid();//创建返回类型ret为void
            }
            else{
                builder.CreateRet(llvm::Constant::getNullValue(returnType));//默认值
            }
        }

        context.popBlock();//跳出函数
    }
    llvm::verifyFunction(*function, &llvm::errs());//可用于验证生成的函数IR是否符合规范

    return function;//返回llvm::Function指针
}

llvm::Value* compoundstmt::codeGen(CodeGenContext& context){
    llvm::IRBuilder<> builder(context.currentBlock());
    llvm::Module* module = context.module;

    llvm::Value* lastValue = nullptr;
    //遍历生成stmtIR
    for (auto &stmt : stmts) {
        if (!stmt) continue;
        lastValue = stmt->codeGen(context);
    }

    // 如果是函数体，ret或ret void
    llvm::Function* function = builder.GetInsertBlock()->getParent();//获取函数返回类型
    if (function->getReturnType()->isVoidTy() && builder.GetInsertBlock()->getTerminator() == nullptr) {
        builder.CreateRetVoid();//没有返回语句或返回void
    }

    //stmt若为空，返回默认值int 0
    if(!lastValue){
        lastValue = llvm::Constant::getNullValve(llvm::Type::getInt32Ty(contaxt.llvmContext));
    }

    return lastValue;
}

llvm::Value* ReturnStmt::codeGen(CodeGenContext& context) {
    llvm::IRBuilder<> builder(context.currentBlock());
    llvm::Module* module = context.module;
    llvm::Function* currentFunction = builder.GetInsertBlock()->getParent();

    //函数返回类型
    llvm::Type* returnType = currentFunction->getReturnType();

    llvm::Value* returnValue = nullptr;
    if (Expression) {
        returnValue = Expression->codeGen(context); // 生成表达式的 IR
    } 

    //ret void
    if (returnType->isVoidTy()){
        builder.CreateRetVoid();
    }
    //ret对应类型
    else{
        builder.CreateRet(returnValue);
    }

    return nullptr; //return语句无后续
}

llvm::Value* AssignStmt::codeGen(CodeGenContext& context) {
    llvm::IRBuilder<> builder(context.currentBlock());
    llvm::Module* module = context.module;

    //查找变量名对应的地址
    llvm::Value* varAddress = context.lookupVariable(identifier);//需要定义lookupVariable方法返回地址
    /*如：
    llvm::Value* CodeGenContext::lookupVariable(const std::string& identifier) {
    // 查找当前作用域（或符号表）中是否有此变量
    auto it = symbolTable.find(identifier);
    if (it != symbolTable.end()) {
        return it->second; // 返回变量的值（通常是地址）
    }
    return nullptr; // 如果找不到，返回 nullptr
}
    */

    //生成expression IR
    llvm::Value* exprValue = expression->codeGen(context);

    //将exprValue值分配给地址varAddress
    builder.CreateStore(exprValue, varAddress);
}

llvm::Value* Expression::codeGen(CodeGenContext& context) {
    //递归生成IR
    if (expression) {
        return expression->codeGen(context);
    }
}

llvm::Value* LOrExp::codeGen(CodeGenContext& context) {
    llvm::IRBuilder<> builder(context.currentBlock());
    
    //生成LHS expr
    llvm::Value* LHS = nullptr;
    if (expression) {
        LHS = expression->codeGen(context);
    }

    //生成RHS expr
    llvm::Value* RHS = nullptr;
    if (LAndExp) {
        RHS = LAndExp->codeGen(context);
    }

    llvm::Type* leftType = LHS->getType();
    llvm::Type* rightType = RHS->getType();
    llvm::Value* leftNonZero = nullptr;
    llvm::Value* rightNonZero = nullptr;

    if (leftType->isIntegerTy() || leftType->isPointerTy()) {//整数或布尔 icmp
        leftNonZero = builder.CreateICmpNE(LHS, llvm::ConstantInt::get(leftType, 0), "leftNonZero");
    } else if (leftType->isFloatingPointTy()) { //浮点数 fcmp
        leftNonZero = builder.CreateFCmpONE(LHS, llvm::ConstantFP::get(leftType, 0.0), "leftNonZero");
    }
    if (rightType->isIntegerTy() || rightType->isPointerTy()) {
        rightNonZero = builder.CreateICmpNE(RHS, llvm::ConstantInt::get(rightType, 0), "rightNonZero");
    } else if (rightType->isFloatingPointTy()) {
        rightNonZero = builder.CreateFCmpONE(RHS, llvm::ConstantFP::get(rightType, 0.0), "rightNonZero");
    }
    //三个basicblock then else merge
    llvm::BasicBlock* thenBlock = llvm::BasicBlock::Create(context.getLLVMContext(), "then", builder.GetInsertBlock()->getParent());
    llvm::BasicBlock* elseBlock = llvm::BasicBlock::Create(context.getLLVMContext(), "else", builder.GetInsertBlock()->getParent());
    llvm::BasicBlock* mergeBlock = llvm::BasicBlock::Create(context.getLLVMContext(), "merge", builder.GetInsertBlock()->getParent());

    builder.CreateCondBr(LeftNonZero, thenBlock, elseBlock);//条件跳转指令，LHS 1跳转then block，0 跳转else block

    //then block: LHS 1（true）
    builder.SetInsertPoint(thenBlock);
    builder.CreateBr(mergeBlock);  //跳转merge blcok

    //else block 如果LHS 0，计算RHS
    builder.SetInsertPoint(elseBlock);
    builder.CreateCondBr(rightNonZero, thenBlock, mergeBlock); //RHS 1，跳转then block，0 跳转merge block

    //merge block
    builder.SetInsertPoint(mergeBlock);

    return nullptr;
}

llvm::Value* LAndExp::codeGen(CodeGenContext& context) {
    llvm::IRBuilder<> builder(context.currentBlock());

    //生成LHS expr
    llvm::Value* LHS = nullptr;
    if (expression) {
        LHS = expression->codeGen(context);
    }

    // 生成RHS expr
    llvm::Value* RHS = nullptr;
    if (LAndExp) {
        RHS = LAndExp->codeGen(context);
    }

    if (leftType->isIntegerTy() || leftType->isPointerTy()) {//整数或布尔 icmp
        leftNonZero = builder.CreateICmpNE(LHS, llvm::ConstantInt::get(leftType, 0), "leftNonZero");
    } else if (leftType->isFloatingPointTy()) { //浮点数 fcmp
        leftNonZero = builder.CreateFCmpONE(LHS, llvm::ConstantFP::get(leftType, 0.0), "leftNonZero");
    }
    if (rightType->isIntegerTy() || rightType->isPointerTy()) {
        rightNonZero = builder.CreateICmpNE(RHS, llvm::ConstantInt::get(rightType, 0), "rightNonZero");
    } else if (rightType->isFloatingPointTy()) {
        rightNonZero = builder.CreateFCmpONE(RHS, llvm::ConstantFP::get(rightType, 0.0), "rightNonZero");
    }

    llvm::BasicBlock* thenBlock = llvm::BasicBlock::Create(context.getLLVMContext(), "then", builder.GetInsertBlock()->getParent());
    llvm::BasicBlock* elseBlock = llvm::BasicBlock::Create(context.getLLVMContext(), "else", builder.GetInsertBlock()->getParent());
    llvm::BasicBlock* mergeBlock = llvm::BasicBlock::Create(context.getLLVMContext(), "merge", builder.GetInsertBlock()->getParent());

    builder.CreateCondBr(leftNonZero, elseBlock, mergeBlock);

    //else block
    builder.SetInsertPoint(elseBlock);
    builder.CreateCondBr(rightNonZero, thenBlock, mergeBlock);
    //then block
    builder.SetInsertPoint(thenBlock);
    //merge block
    builder.SetInsertPoint(mergeBlock);

    return nullptr;
}

llvm::Value* EqExp::codeGen(CodeGenContext& context) {
    llvm::IRBuilder<> builder(context.currentBlock());

    //LHS IR
    llvm::Value* LHS = nullptr;
    if (expression) {
        LHS = expression->codeGen(context);
    }

    //RHS IR
    llvm::Value* RHS = nullptr;
    if (RelExp) {
        RHS = RelExp->codeGen(context);
    }

    llvm::Type* leftType = LHS->getType();
    llvm::Type* rightType = RHS->getType();
    llvm::Value* result = nullptr;

    //int or boolean ICmp
    if (leftType->isIntegerTy() || leftType->isPointerTy()) {
        if (op == "==") {
            result = builder.CreateICmpEQ(LHS, RHS, "eq_result");
        } else if (op == "!=") {
            result = builder.CreateICmpNE(LHS, RHS, "neq_result");
        }
    } 
    //float FCmp
    else if (leftType->isFloatingPointTy()) {
        if (op == "==") {
            result = builder.CreateFCmpOEQ(LHS, RHS, "eq_result");
        } else if (op == "!=") {
            result = builder.CreateFCmpONE(LHS, RHS, "neq_result");
        }
    }
    return result;
}


llvm::Value* RelExp::codeGen(CodeGenContext& context) {
    llvm::IRBuilder<> builder(context.currentBlock());
    llvm::Module* module = context.module;
    
    llvm::Value* LHS = expression->codeGen(context);
    llvm::Value* RHS = AddExp->codeGen(context);
    
    llvm::Value* result = nullptr;
    if (LHS->getType()->isIntegerTy()) {
        if (op == "<") {
            result = builder.CreateICmpSLT(LHS, RHS, "cmplt");
        } 
        else if (op == "<=") {
            result = builder.CreateICmpSLE(LHS, RHS, "cmple");
        } 
        else if (op == ">") {
            result = builder.CreateICmpSGT(LHS, RHS, "cmpgt");
        } 
        else if (op == ">=") {
            result = builder.CreateICmpSGE(LHS, RHS, "cmpge");
        }
    } else if (LHS->getType()->isFloatingPointTy()) {
        if (op == "<") {
            result = builder.CreateFCmpULT(LHS, RHS, "cmplt");
        } 
        else if (op == "<=") {
            result = builder.CreateFCmpULE(LHS, RHS, "cmple");
        } 
        else if (op == ">") {
            result = builder.CreateFCmpUGT(LHS, RHS, "cmpgt");
        } 
        else if (op == ">=") {
            result = builder.CreateFCmpUGE(LHS, RHS, "cmpge");
        }
    }
    return result;
}

llvm::Value* AddExp::codeGen(CodeGenContext& context) {
    llvm::IRBuilder<> builder(context.currentBlock());

    llvm::Value* leftValue = nullptr;
    if (expression) {
        leftValue = expression->codeGen(context);
    }

    llvm::Value* rightValue = nullptr;
    if (MulExp) {
        rightValue = MulExp->codeGen(context);
    }

    llvm::Type* leftType = leftValue->getType();
    llvm::Type* rightType = rightValue->getType();
    llvm::Value* result = nullptr;

    if (leftType->isIntegerTy()) {
        if (op == "+") {
            result = builder.CreateAdd(leftValue, rightValue, "add_result");
        } 
        else if (op == "-") {
            result = builder.CreateSub(leftValue, rightValue, "sub_result");
        }
    }

    else if (leftType->isFloatingPointTy()) {
        if (op == "+") {
            result = builder.CreateFAdd(leftValue, rightValue, "fadd_result");
        } 
        else if (op == "-") {
            result = builder.CreateFSub(leftValue, rightValue, "fsub_result");
        }
    }

    return result;
}

llvm::Value* MulExp::codeGen(CodeGenContext& context) {
    llvm::IRBuilder<> builder(context.currentBlock());

    llvm::Value* leftValue = nullptr;
    if (expression) {
        leftValue = expression->codeGen(context);
    }

    llvm::Value* rightValue = nullptr;
    if (UnaryExp) {
        rightValue = UnaryExp->codeGen(context);
    }

    llvm::Type* leftType = leftValue->getType();
    llvm::Type* rightType = rightValue->getType();
    llvm::Value* result = nullptr;

    if (leftType->isIntegerTy()) {
        if (op == "*") {
            result = builder.CreateMul(leftValue, rightValue, "mul_result");
        } 
        else if (op == "/") {
            result = builder.CreateSDiv(leftValue, rightValue, "div_result");
        } 
        else if (op == "%") {
            result = builder.CreateSRem(leftValue, rightValue, "mod_result");
        }
    } 
    else if (leftType->isFloatingPointTy()) {
        if (op == "*") {
            result = builder.CreateFMul(leftValue, rightValue, "fmul_result");
        } 
        else if (op == "/") {
            result = builder.CreateFDiv(leftValue, rightValue, "fdiv_result");
        } 
    }
    return result;
}

llvm::Value* UnaryExp::codeGen(CodeGenContext& context) {
    llvm::IRBuilder<> builder(context.currentBlock());

    llvm::Value* operand = nullptr;
    if (unaryExp) {
        operand = unaryExp->codeGen(context);
    }

    llvm::Value* result = nullptr;
    if (expression) {
        std::string op = expression->GetNodeType();

        if (op == "-") {
            if (operand->getType()->isIntegerTy()) {
                result = builder.CreateNeg(operand, "neg_result");
            } 
            else if (operand->getType()->isFloatingPointTy()) {
                result = builder.CreateFNeg(operand, "fneg_result");
            }
        } else if (op == "!") {
            llvm::Value* zero = llvm::Constant::getNullValue(operand->getType());
            result = builder.CreateICmpEQ(operand, zero, "not_result");
        }
        else if (opType == "+") {
        result = operand;
    }
    return result;
}

llvm::Value* PrimaryExp::codeGen(CodeGenContext& context) {
    if (expression) {
        return expression->codeGen(context);
    } 
    else if (!str.empty()) {
        if (isdigit(str[0]) || (str[0] == '-' && isdigit(str[1]))) {
            try {
                int intValue = std::stoi(str);
                return llvm::ConstantInt::get(context.getLLVMContext(), llvm::APInt(32, intValue));
            } catch (...) {
                try {
                    double floatValue = std::stod(str);
                    return llvm::ConstantFP::get(context.getLLVMContext(), llvm::APFloat(floatValue));
                }
            }
        }
    }
    return nullptr;
}

llvm::Value* ConstDecl::codeGen(CodeGenContext& context) {
    llvm::IRBuilder<> builder(context.currentBlock());
    llvm::Type* llvmType = nullptr;

    //生成类型
    llvmType = type->codeGen(context);

    //处理单个 ConstDef
    llvm::Value* constDefValue = ConstDef->codeGen(context);

    //创建全局变量
    llvm::GlobalVariable* globalVar = new llvm::GlobalVariable(
        *context.module,
        llvmType,
        true,        
        llvm::GlobalValue::ExternalLinkage,
        llvm::cast<llvm::Constant>(constDefValue),
        identifier
    );

    //多个ConstDef
    for (auto& def : ConstDefs) {
        llvm::Value* multiConstDefValue = def->codeGen(context);

        new llvm::GlobalVariable(
            *context.module, 
            llvmType, 
            true, 
            llvm::GlobalValue::ExternalLinkage, 
            llvm::cast<llvm::Constant>(multiConstDefValue), 
            def->getName()
        );
    }

    return globalVar;
}


llvm::Value* ConstDef::codeGen(CodeGenContext& context) {
    llvm::IRBuilder<> builder(context.currentBlock());
    llvm::Type* llvmType = nullptr;

    llvm::Value* constValue = expression->codeGen(context);
    //数组初始化
    if (array_size) {
        llvm::Value* arraySizeValue = array_size->codeGen(context);
        //数组类型
        llvmType = llvm::ArrayType::get(constValue->getType(), arraySizeValue);

        std::vector<llvm::Constant*> constArrayElements;
        for (auto& elem : array) {
            llvm::Value* arrayElem = elem->codeGen(context);
            constArrayElements.push_back(llvm::cast<llvm::Constant>(arrayElem));
        }

        // 创建全局数组
        llvm::GlobalVariable* globalArray = new llvm::GlobalVariable(
            *context.module,
            llvmType,
            true,
            llvm::GlobalValue::ExternalLinkage,
            llvm::ConstantArray::get(llvm::cast<llvm::ArrayType>(llvmType), constArrayElements),
            identifier
        );

        return globalArray;
    }

    //不是数组
    llvmType = constValue->getType();
    llvm::GlobalVariable* globalVar = new llvm::GlobalVariable(
        *context.module,
        llvmType,
        true,
        llvm::GlobalValue::ExternalLinkage,
        llvm::cast<llvm::Constant>(constValue),
        identifier
    );

    return globalVar;
}

llvm::Value* VarDecl::codeGen(CodeGenContext& context) {
    llvm::IRBuilder<> builder(context.currentBlock());
    llvm::Type* llvmType = nullptr;

    llvmType = type->codeGen(context);

    llvm::Value* varDefValue = VarDef->codeGen(context);

    llvm::GlobalVariable* globalVar = new llvm::GlobalVariable(
        *context.module,
        llvmType,
        false,
        llvm::GlobalValue::ExternalLinkage,
        llvm::cast<llvm::Constant>(varDefValue),
        identifier
    );

    for (auto& def : VarDefs) {
        llvm::Value* multiVarDefValue = def->codeGen(context);

        new llvm::GlobalVariable(
            *context.module, 
            llvmType, 
            false, 
            llvm::GlobalValue::ExternalLinkage, 
            llvm::cast<llvm::Constant>(multiVarDefValue), 
            def->getName()
        );
    }

    return globalVar;
}

llvm::Value* VarDef::codeGen(CodeGenContext& context) {
    llvm::IRBuilder<> builder(context.currentBlock());
    
    //变量类型
    llvm::Type* llvmType = nullptr;
    if (expression) {
        llvmType = expression->codeGen(context);
    }

    //数组
    if (array_size) {
        llvm::Value* sizeValue = array_size->codeGen(context);
        llvm::ArrayType* arrayType = llvm::ArrayType::get(llvmType, sizeValue);
        
        //数组全局变量
        llvm::GlobalVariable* globalArray = new llvm::GlobalVariable(*context.module, arrayType, false, llvm::GlobalValue::ExternalLinkage, nullptr, identifier);
        
        for (size_t i = 0; i < array.size(); ++i) {
            llvm::Value* arrayElementValue = array[i]->codeGen(context);
            llvm::Constant* index = llvm::ConstantInt::get(llvm::Type::getInt32Ty(context.context), i);
            builder.CreateStore(arrayElementValue, builder.CreateGEP(globalArray, {index}));
        }
        return globalArray;
    }

    if (expression) {
        llvm::Value* varValue = expression->codeGen(context);
        llvm::GlobalVariable* globalVar = new llvm::GlobalVariable(*context.module, llvmType, false, llvm::GlobalValue::ExternalLinkage, llvm::cast<llvm::Constant>(varValue), identifier);
        return globalVar;
    }
    
    return nullptr;
}

llvm::Value* IFStmt::codeGen(CodeGenContext& context) {
    llvm::Value* condVal = condition->codeGen(context);
    
    llvm::BasicBlock* thenBlock = llvm::BasicBlock::Create(context.context, "then");
    llvm::BasicBlock* elseBlock = llvm::BasicBlock::Create(context.context, "else");
    llvm::BasicBlock* mergeBlock = llvm::BasicBlock::Create(context.context, "merge");

    llvm::IRBuilder<> builder(context.builder);
    builder.CreateCondBr(condVal, thenBlock, elseBlock);

    //if
    context.currentFunction->getBasicBlockList().push_back(thenBlock);
    builder.SetInsertPoint(thenBlock);
    body->codeGen(context);
    builder.CreateBr(mergeBlock);

    //else
    context.currentFunction->getBasicBlockList().push_back(elseBlock);
    builder.SetInsertPoint(elseBlock);
    if (else_body) {
        else_body->codeGen(context);
    }
    builder.CreateBr(mergeBlock);

    // 结束
    context.currentFunction->getBasicBlockList().push_back(mergeBlcok);
    builder.SetInsertPoint(mergeBlock);

    return nullptr;
}

llvm::Value* WhileStmt::codeGen(CodeGenContext& context) {
    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(context.context, "entry");
    llvm::BasicBlock* loopBodyBlock = llvm::BasicBlock::Create(context.context, "loop_body");
    llvm::BasicBlock* loopEndBlock = llvm::BasicBlock::Create(context.context, "loop_end");

    //entryBlock
    llvm::IRBuilder<> builder(context.builder);
    builder.CreateBr(entryBlock);
    context.currentFunction->getBasicBlockList().push_back(entryBlock);
    builder.SetInsertPoint(entryBlock);

    //条件
    llvm::Value* condVal = condition->codeGen(context);

    builder.CreateCondBr(condVal, loopBodyBlock, loopEndBlock);

    context.currentFunction->getBasicBlockList().push_back(loopBodyBlock);
    builder.SetInsertPoint(loopBodyBlock);
    body->codeGen(context);
    builder.CreateBr(entryBlock);  //跳回条件检查

    //End
    context.currentFunction->getBasicBlockList().push_back(loopEndBlock);
    builder.SetInsertPoint(loopEndBlock);

    return nullptr;  // 没有返回值
}

llvm::Value* ForStmt::codeGen(CodeGenContext& context) {
    llvm::BasicBlock* entryBlock = llvm::BasicBlock::Create(context.context, "entry");
    llvm::BasicBlock* loopCondBlock = llvm::BasicBlock::Create(context.context, "loop_cond");
    llvm::BasicBlock* loopBodyBlock = llvm::BasicBlock::Create(context.context, "loop_body");
    llvm::BasicBlock* loopEndBlock = llvm::BasicBlock::Create(context.context, "loop_end");

    //entryBlock
    llvm::IRBuilder<> builder(context.builder);
    builder.CreateBr(entryBlock);
    context.currentFunction->getBasicBlockList().push_back(entryBlock);
    builder.SetInsertPoint(entryBlock);

    if (init) {
        init->codeGen(context);
    }
    
    context.currentFunction->getBasicBlockList().push_back(loopCondBlock);
    builder.CreateBr(loopCondBlock);
    builder.SetInsertPoint(loopCondBlock);
    
    llvm::Value* condVal = condition->codeGen(context);

    builder.CreateCondBr(condVal, loopBodyBlock, loopEndBlock);

    context.currentFunction->getBasicBlockList().push_back(loopBodyBlock);
    builder.SetInsertPoint(loopBodyBlock);
    body->codeGen(context);

    increment->codeGen(context);

    builder.CreateBr(loopCondBlock);

    context.currentFunction->getBasicBlockList().push_back(loopEndBlock);
    builder.SetInsertPoint(loopEndBlock);

    return nullptr;
}

llvm::Value* LValue::codeGen(CodeGenContext& context) {
    llvm::Value* varAddress = context.getVariableAddress(name);

    return varAddress;
}


llvm::Value* BreakStmt::codeGen(CodeGenContext& context) {
    //跳转到当前break block
    return llvm::BranchInst::Create(context.currentBreakBlock, context.currentBlock());
}

llvm::Value* ContinueStmt::codeGen(CodeGenContext& context) {

    //跳转到当前continue block
    return llvm::BranchInst::Create(context.currentContinueBlock, context.currentBlock());
}

/*
void CodeGenContext::enterLoop(llvm::BasicBlock* breakBlock) {
    loopBreakStack.push(currentBreakBlock);
    currentBreakBlock = breakBlock;
}

void CodeGenContext::exitLoop() {
    if (!loopBreakStack.empty()) {
        currentBreakBlock = loopBreakStack.top();
        loopBreakStack.pop();
    } else {
        currentBreakBlock = nullptr;
    }
}
*/

/*
void CodeGenContext::enterLoop(llvm::BasicBlock* continueBlock, llvm::BasicBlock* breakBlock) {
    loopContinueStack.push(currentContinueBlock);
    loopBreakStack.push(currentBreakBlock);
    currentContinueBlock = continueBlock;
    currentBreakBlock = breakBlock;
}

void CodeGenContext::exitLoop() {
    if (!loopContinueStack.empty()) {
        currentContinueBlock = loopContinueStack.top();
        loopContinueStack.pop();
    } else {
        currentContinueBlock = nullptr;
    }

    if (!loopBreakStack.empty()) {
        currentBreakBlock = loopBreakStack.top();
        loopBreakStack.pop();
    } else {
        currentBreakBlock = nullptr;
    }
}

*/


llvm::Value* EXP::codeGen(CodeGenContext& context) {
    if (IDEN) {
        llvm::Value* variable = context.getValue(value);
        return new llvm::LoadInst(variable, "", false, context.currentBlock());
    }

    if (!Left && !Right) {
        if (isdigit(value[0]) || (value[0] == '-' && value.size() > 1)) {
            return llvm::ConstantInt::get(llvm::Type::getInt32Ty(context.llvmContext), std::stoi(value), true);
        }
    }

    //左右递归
    llvm::Value* leftValue = Left ? Left->codeGen(context) : nullptr;
    llvm::Value* rightValue = Right ? Right->codeGen(context) : nullptr;

    //运算符
    if (value == "+") {
        return llvm::BinaryOperator::CreateAdd(leftValue, rightValue, "", context.currentBlock());
    } else if (value == "-") {
        return llvm::BinaryOperator::CreateSub(leftValue, rightValue, "", context.currentBlock());
    } else if (value == "*") {
        return llvm::BinaryOperator::CreateMul(leftValue, rightValue, "", context.currentBlock());
    } else if (value == "/") {
        return llvm::BinaryOperator::CreateSDiv(leftValue, rightValue, "", context.currentBlock());
    } else if (value == "%") {
        return llvm::BinaryOperator::CreateSRem(leftValue, rightValue, "", context.currentBlock());
    } else if (value == "==") {
        return llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_EQ, leftValue, rightValue, "", context.currentBlock());
    } else if (value == "!=") {
        return llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_NE, leftValue, rightValue, "", context.currentBlock());
    } else if (value == "<") {
        return llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SLT, leftValue, rightValue, "", context.currentBlock());
    } else if (value == ">") {
        return llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SGT, leftValue, rightValue, "", context.currentBlock());
    } else if (value == "<=") {
        return llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SLE, leftValue, rightValue, "", context.currentBlock());
    } else if (value == ">=") {
        return llvm::CmpInst::Create(llvm::Instruction::ICmp, llvm::CmpInst::ICMP_SGE, leftValue, rightValue, "", context.currentBlock());
    }
}

llvm::Value* StructDecl::codeGen(CodeGenContext& context) {
    std::vector<llvm::Type*> structFields;

    for (auto& field : body->getFields()) {
        llvm::Type* fieldType = field->getLLVMType(context);
        structFields.push_back(fieldType);
    }

    llvm::StructType* structType = llvm::StructType::create(context.llvmContext, structFields, name);

    //结构体实例
    llvm::AllocaInst* allocaInst = context.createAlloca(structType, name);

    //初始化值赋值
    for (size_t i = 0; i < structFields.size(); ++i) {
        llvm::Value* fieldValue = body->getFieldValue(i);
        llvm::StoreInst* storeInst = new llvm::StoreInst(fieldValue, allocaInst, context.currentBlock());
    }

    return allocaInst;
}

llvm::Value* StructBody::codeGen(CodeGenContext& context) {
    std::vector<llvm::Type*> structFields;

    for (auto& field : body) {
        llvm::Type* fieldType = field->getLLVMType(context);
        structFields.push_back(fieldType);
    }

    llvm::StructType* structType = llvm::StructType::create(context.llvmContext, structFields, "structName");
    return structType;
}

llvm::Value* FunctionParameters::codeGen(CodeGenContext& context) {
    llvm::Type* llvmType = type->getLLVMType(context);
    
    // 使用参数类型和标识符来创建参数
    llvm::FunctionType* functionType = llvm::FunctionType::get(llvmType, false); // 返回一个函数类型
    llvm::Argument* argument = llvm::Argument::Create(llvmType, IDEN, nullptr);

    return argument;
}

