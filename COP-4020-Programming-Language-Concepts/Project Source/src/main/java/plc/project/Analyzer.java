package plc.project;

import com.sun.org.apache.xpath.internal.Arg;

import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

/**
 * See the specification for information about what the different visit
 * methods should do.
 */
public final class Analyzer implements Ast.Visitor<Void> {

    public Scope scope;
    private Ast.Method method;

    public Analyzer(Scope parent) {
        scope = new Scope(parent);
        scope.defineFunction("print", "System.out.println", Arrays.asList(Environment.Type.ANY), Environment.Type.NIL, args -> Environment.NIL);
    }

    public Scope getScope() {
        return scope;
    }

    @Override
    public Void visit(Ast.Source ast) {
        Environment.Function main;
        for(Ast.Field field : ast.getFields()){
            visit(field);
        }
        for(Ast.Method method : ast.getMethods()){
            visit(method);
        }
        main = scope.lookupFunction("main",0);
        if(main.getReturnType() != Environment.Type.INTEGER){
            throw new RuntimeException("Main method does not have integer return type");
        }
        return null;
    }

    @Override
    public Void visit(Ast.Field ast) {
        Environment.Variable var;
        if(ast.getValue().isPresent()){
            visit(ast.getValue().get());
            requireAssignable(Environment.getType(ast.getTypeName()),ast.getValue().get().getType());
        }
        var = scope.defineVariable(ast.getName(),ast.getName(), Environment.getType(ast.getTypeName()),Environment.NIL);
        ast.setVariable(var);
        return null;
    }

    @Override
    public Void visit(Ast.Method ast) {
        Environment.Function func;
        List<Environment.Type> typeList = new ArrayList<>();
        for(String name : ast.getParameterTypeNames()){
            typeList.add(Environment.getType(name));
        }
        if(ast.getReturnTypeName().isPresent()){
            func = scope.defineFunction(ast.getName(),ast.getName(),typeList,Environment.getType(ast.getReturnTypeName().get()),args -> Environment.NIL);
            ast.setFunction(func);
        }
        else{
            func = scope.defineFunction(ast.getName(),ast.getName(),typeList,Environment.Type.NIL,args -> Environment.NIL);
            ast.setFunction(func);
        }
        Scope methodScope = scope;
        scope = new Scope(scope);
        scope.defineVariable("RETURN","RETURN",func.getReturnType(),Environment.NIL);
        for(int i = 0; i < ast.getParameters().size(); i++){
            scope.defineVariable(ast.getParameters().get(i),ast.getParameters().get(i),Environment.getType(ast.getParameterTypeNames().get(i)),Environment.NIL);
        }
        for(Ast.Stmt stmt : ast.getStatements()){
            visit(stmt);
        }
        scope = methodScope;
        return null;
    }

    @Override
    public Void visit(Ast.Stmt.Expression ast){
        if(ast.getExpression() instanceof Ast.Expr.Function){
            visit(ast.getExpression());
            return null;
        }
        else{
            throw new RuntimeException("Stmt.Expression is not a function");
        }
    }

    @Override
    public Void visit(Ast.Stmt.Declaration ast) {
        if(ast.getValue().isPresent()){
            visit(ast.getValue().get());
            if(ast.getTypeName().isPresent()){
                requireAssignable(ast.getValue().get().getType(),Environment.getType(ast.getTypeName().get()));
            }
            scope.defineVariable(ast.getName(),ast.getName(),ast.getValue().get().getType(),Environment.NIL);
            ast.setVariable(scope.lookupVariable(ast.getName()));
            return null;
        }
        else{
            if(!ast.getTypeName().isPresent()){
                throw new RuntimeException("No type name provided for declaration");
            }
            else{
                scope.defineVariable(ast.getName(),ast.getName(),Environment.getType(ast.getTypeName().get()),Environment.NIL);
                ast.setVariable(scope.lookupVariable(ast.getName()));
            }
            return null;
        }
    }

    @Override
    public Void visit(Ast.Stmt.Assignment ast) {
        if(ast.getReceiver() instanceof Ast.Expr.Access){
            visit(ast.getReceiver());
            visit(ast.getValue());
            requireAssignable(ast.getReceiver().getType(),ast.getValue().getType());
            return null;
        }
        else{
            throw new RuntimeException("Assignment receiver is not an Access expression");
        }
    }

    @Override
    public Void visit(Ast.Stmt.If ast) {
        visit(ast.getCondition());
        if(ast.getCondition().getType() != Environment.Type.BOOLEAN){
            throw new RuntimeException("If statement condition is not a Boolean");
        }
        else if(ast.getThenStatements().isEmpty()){
            throw new RuntimeException("If statement has no Then statements");
        }
        else{
            Scope ifScope = scope;
            scope = new Scope(scope);
            for(Ast.Stmt stmt : ast.getThenStatements()){
                visit(stmt);
            }
            if(!ast.getElseStatements().isEmpty()) {
                scope = new Scope(ifScope);
                for (Ast.Stmt stmt : ast.getElseStatements()) {
                    visit(stmt);
                }
            }
            scope = ifScope;
            return null;
        }
    }

    @Override
    public Void visit(Ast.Stmt.For ast) {
        visit(ast.getValue());
        if(ast.getValue().getType() != Environment.Type.INTEGER_ITERABLE){
            throw new RuntimeException("For loop value is not integer_iterable");
        }
        else if(ast.getStatements().isEmpty()){
            throw new RuntimeException("For loop has no statements");
        }
        else{
            Scope forScope = scope;
            scope = new Scope(scope);
            scope.defineVariable(ast.getName(),ast.getName(), Environment.Type.INTEGER,Environment.NIL);
            for(Ast.Stmt stmt : ast.getStatements()){
                visit(stmt);
            }
            scope = forScope;
            return null;
        }
    }

    @Override
    public Void visit(Ast.Stmt.While ast) {
        visit(ast.getCondition());
        if(ast.getCondition().getType() != Environment.Type.BOOLEAN){
            throw new RuntimeException("While loop condition is not a Boolean");
        }
        else{
            Scope whileScope = scope;
            scope = new Scope(scope);
            for(Ast.Stmt stmt : ast.getStatements()){
                visit(stmt);
            }
            scope = whileScope;
            return null;
        }
    }

    @Override
    public Void visit(Ast.Stmt.Return ast) {
        visit(ast.getValue());
        requireAssignable(scope.lookupVariable("RETURN").getType(),ast.getValue().getType());
        return null;
    }

    @Override
    public Void visit(Ast.Expr.Literal ast) {
        if(ast.getLiteral() == null){
            ast.setType(Environment.Type.NIL);
        }
        else if(ast.getLiteral() instanceof Boolean){
            ast.setType(Environment.Type.BOOLEAN);
        }
        else if(ast.getLiteral() instanceof String){
            ast.setType(Environment.Type.STRING);
        }
        else if(ast.getLiteral() instanceof Character){
            ast.setType(Environment.Type.CHARACTER);
        }
        else if(ast.getLiteral() instanceof BigInteger){
            if(((BigInteger) ast.getLiteral()).compareTo(new BigInteger("2147483647")) > 0 || ((BigInteger) ast.getLiteral()).compareTo(new BigInteger("-2147483648")) < 0){
                throw new RuntimeException("Integer exceeds max 32 bits");
            }
            else {
                ast.setType(Environment.Type.INTEGER);
            }
        }
        else if(ast.getLiteral() instanceof BigDecimal){
            if(((BigDecimal) ast.getLiteral()).compareTo(new BigDecimal(Double.MAX_VALUE)) > 0 || ((BigDecimal) ast.getLiteral()).compareTo(new BigDecimal(-Double.MAX_VALUE)) < 0){
                throw new RuntimeException("Decimal exceeds max 64 bit float");
            }
            else{
                ast.setType(Environment.Type.DECIMAL);
            }
        }
        return null;
    }

    @Override
    public Void visit(Ast.Expr.Group ast) {
        if (ast.getExpression() instanceof Ast.Expr.Binary) {
            visit(ast.getExpression());
            ast.setType(((Ast.Expr.Binary) ast.getExpression()).getType());
            return null;
        }
        else{
            throw new RuntimeException("Group does not contain a binary expression");
        }
    }

    @Override
    public Void visit(Ast.Expr.Binary ast) {
        visit(ast.getLeft());
        visit(ast.getRight());
        if(ast.getOperator()=="AND"||ast.getOperator()=="OR"){
            if(ast.getLeft().getType()== Environment.Type.BOOLEAN && ast.getRight().getType()== Environment.Type.BOOLEAN){
                ast.setType(Environment.Type.BOOLEAN);
                return null;
            }
            else {
                throw new RuntimeException("Binary AND/OR must have boolean left/right expressions");
            }
        }
        else if(ast.getOperator()=="<"||ast.getOperator()==">"||ast.getOperator()=="<="||ast.getOperator()==">="||ast.getOperator()=="=="||ast.getOperator()=="!="){
            if(ast.getLeft().getType()==ast.getRight().getType()){
                if(ast.getLeft().getType()== Environment.Type.INTEGER || ast.getLeft().getType()== Environment.Type.DECIMAL || ast.getLeft().getType()== Environment.Type.STRING || ast.getLeft().getType()== Environment.Type.CHARACTER){
                    ast.setType(ast.getLeft().getType());
                    return null;
                }
                else{
                    throw new RuntimeException("Comparison with non-comparable types");
                }
            }
            else{
                throw new RuntimeException("Comparison with different types");
            }
        }
        else if(ast.getOperator()=="+"){
            if(ast.getLeft().getType()== Environment.Type.STRING || ast.getRight().getType()== Environment.Type.STRING){
                ast.setType(Environment.Type.STRING);
                return null;
            }
            else if(ast.getLeft().getType()== Environment.Type.DECIMAL || ast.getLeft().getType()== Environment.Type.INTEGER){
                if(ast.getLeft().getType()==ast.getRight().getType()){
                    ast.setType(ast.getLeft().getType());
                    return null;
                }
                else{
                    throw new RuntimeException("Non-matching number types");
                }
            }
        }
        else if(ast.getOperator()=="-" || ast.getOperator()=="/" || ast.getOperator()=="*"){
            if(ast.getLeft().getType()== Environment.Type.DECIMAL || ast.getLeft().getType()== Environment.Type.INTEGER){
                if(ast.getLeft().getType()==ast.getRight().getType()){
                    ast.setType(ast.getLeft().getType());
                    return null;
                }
                else{
                    throw new RuntimeException("Non-matching number types");
                }
            }
        }
        return null;
    }

    @Override
    public Void visit(Ast.Expr.Access ast) {
        if(ast.getReceiver().isPresent()){
            visit(ast.getReceiver().get());
            ast.setVariable(ast.getReceiver().get().getType().getScope().lookupVariable(ast.getName()));
            return null;
        }
        else {
            ast.setVariable(scope.lookupVariable(ast.getName()));
            return null;
        }
    }

    @Override
    public Void visit(Ast.Expr.Function ast) {
        List<Environment.Type> ArgTypes =new ArrayList<>();
        List<Environment.Type> ParamTypes = null;
        for(Ast.Expr expr : ast.getArguments()){
            visit(expr);
            ArgTypes.add(expr.getType());
        }
        if(!ast.getReceiver().isPresent()){
            ParamTypes = scope.lookupFunction(ast.getName(),ast.getArguments().size()).getParameterTypes();
            for(int i = 0; i < ArgTypes.size(); i++){
                requireAssignable(ParamTypes.get(i), ArgTypes.get(i));
            }
            ast.setFunction(scope.lookupFunction(ast.getName(),ParamTypes.size()));
            return null;
        }
        else{
            visit(ast.getReceiver().get());
            ParamTypes = ast.getReceiver().get().getType().getScope().lookupFunction(ast.getName(),ArgTypes.size()+1).getParameterTypes();
            for(int i = 0; i < ArgTypes.size(); i++){
                requireAssignable(ArgTypes.get(i), ParamTypes.get(i+1));
            }
            ast.setFunction(ast.getReceiver().get().getType().getScope().lookupFunction(ast.getName(),ParamTypes.size()));
            return null;
        }
    }

    public static void requireAssignable(Environment.Type target, Environment.Type type) {
        String targetName = target.getName();
        String typeName = type.getName();
        if(targetName=="Any" || targetName==typeName){
            return;
        }
        else if(targetName=="Comparable"){
            if(typeName=="Decimal" || typeName=="Character" || typeName=="String" || typeName=="Integer"){
                return;
            }
            else
                throw new RuntimeException("Type is not comparable");
        }
        else
            throw new RuntimeException("Type is not assignable");
    }

}
