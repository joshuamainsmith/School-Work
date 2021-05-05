/*
package plc.project;

import com.sun.org.apache.xpath.internal.Arg;

import java.math.BigDecimal;
import java.math.BigInteger;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

*/
/**
 * See the specification for information about what the different visit
 * methods should do.
 *//*

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
        boolean mainPresent = false, returnPresent = false;
        for(Ast.Field f : ast.getFields()){
            visit(f);
        }
        for(Ast.Method m : ast.getMethods()){
            visit(m);
            if (m.getName().equals("main") && m.getParameters().isEmpty()) {
                mainPresent = true;
            }

            if (m.getName().equals("END")) {        // Check on return statement probably wrong
                returnPresent = true;
            }
        }
        if (!mainPresent) {
            throw new RuntimeException("Main function not present");
        }
        if (!returnPresent) {
            throw new RuntimeException("Return not present");
        }
        return null;
        //throw new UnsupportedOperationException();  // TODO
    }

    @Override
    public Void visit(Ast.Field ast) {
        return null;
        //throw new UnsupportedOperationException();  // TODO
    }

    @Override
    public Void visit(Ast.Method ast) {
        return null;
        //throw new UnsupportedOperationException();  // TODO
    }

    @Override
    public Void visit(Ast.Stmt.Expression ast) {
        visit(ast.getExpression());
        if (!(ast.getExpression() instanceof Ast.Expr.Function)) {
            throw new RuntimeException("Expression is not of type Function");
        }
        return null;
        //throw new UnsupportedOperationException();  // TODO
    }

    @Override
    public Void visit(Ast.Stmt.Declaration ast) {

        if (ast.getValue().isPresent()) {
            visit(ast.getValue().get());
            ast.setVariable(scope.defineVariable(ast.getName(), ast.getName(), ast.getValue().get().getType(), Environment.NIL));
        }
        else {
            Optional<String> n = ast.getTypeName();
            if (n.equals(Optional.empty())) {
                throw new RuntimeException("No type given");
            }

            Environment.Type v = null;
            switch (n.get()) {
                case "Any":
                    v = Environment.Type.ANY;
                    break;
                case "Nil":
                    v = Environment.Type.NIL;
                    break;
                case "IntegerIterable":
                    v = Environment.Type.INTEGER_ITERABLE;
                    break;
                case "Comparable":
                    v = Environment.Type.COMPARABLE;
                    break;
                case "Boolean":
                    v = Environment.Type.BOOLEAN;
                    break;
                case "Integer":
                    v = Environment.Type.INTEGER;
                    break;
                case "Decimal":
                    v = Environment.Type.DECIMAL;
                    break;
                case "Character":
                    v = Environment.Type.CHARACTER;
                    break;
                case "String":
                    v = Environment.Type.STRING;
                    break;
            }
            if (v == null) {
                throw new RuntimeException("Unknown type");
            }
            ast.setVariable(scope.defineVariable(ast.getName(), ast.getName(), v, Environment.NIL));
        }
        return null;
        //throw new UnsupportedOperationException();  // TODO
    }

    @Override
    public Void visit(Ast.Stmt.Assignment ast) {        // Need to check if value is assignable to receiver
        visit(ast.getValue());
        visit(ast.getReceiver());
        if (!(ast.getReceiver() instanceof Ast.Expr.Access)) {
            throw new RuntimeException("Receiver not of type Access Expression");
        }
        requireAssignable(ast.getReceiver().getType(), ast.getValue().getType());

        return null;
        //throw new UnsupportedOperationException();  // TODO
    }

    @Override
    public Void visit(Ast.Stmt.If ast) {
        visit(ast.getCondition());
        requireAssignable(Environment.Type.BOOLEAN, ast.getCondition().getType());

        if (ast.getThenStatements().isEmpty()) {
            throw new RuntimeException("Then Statements List Empty");
        }
        try {
            scope = new Scope(scope);
            for (Ast.Stmt stmt : ast.getThenStatements()) {
                visit(stmt);
            }
        } finally {
            scope = scope.getParent();
        }

        if (!ast.getElseStatements().isEmpty()) {
            try {
                scope = new Scope(scope);
                for (Ast.Stmt stmt : ast.getElseStatements()) {
                    visit(stmt);
                }
            } finally {
                scope = scope.getParent();
            }
        }
        return null;
        //throw new UnsupportedOperationException();  // TODO
    }

    @Override
    public Void visit(Ast.Stmt.For ast) {       // Need to do various scope variable checks
        visit(ast.getValue());
        requireAssignable(Environment.Type.INTEGER_ITERABLE, ast.getValue().getType());
        if (ast.getStatements().isEmpty()) {
            throw new RuntimeException("Statements List Empty");
        }
        try {
            scope = new Scope(scope);
            for (Ast.Stmt stmt : ast.getStatements()) {
                visit(stmt);
            }
        } finally {
            scope = scope.getParent();
        }

        return null;
        //throw new UnsupportedOperationException();  // TODO
    }

    @Override
    public Void visit(Ast.Stmt.While ast) {
        visit(ast.getCondition());
        requireAssignable(Environment.Type.BOOLEAN, ast.getCondition().getType());
        try {
            scope = new Scope(scope);
            for (Ast.Stmt stmt : ast.getStatements()) {
                visit(stmt);
            }
        } finally {
            scope = scope.getParent();
        }
        return null;
        //throw new UnsupportedOperationException();  // TODO
    }

    @Override
    public Void visit(Ast.Stmt.Return ast) {
        return null;
        //throw new UnsupportedOperationException();  // TODO
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
*/
