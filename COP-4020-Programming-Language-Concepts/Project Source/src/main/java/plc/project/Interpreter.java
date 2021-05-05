package plc.project;

import java.math.BigDecimal;
import java.math.BigInteger;
import java.math.RoundingMode;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;
import java.util.Optional;

public class Interpreter implements Ast.Visitor<Environment.PlcObject> {

    private Scope scope = new Scope(null);

    public Interpreter(Scope parent) {
        scope = new Scope(parent);
        scope.defineFunction("print", 1, args -> {
            System.out.println(args.get(0).getValue());
            return Environment.NIL;
        });
    }

    public Scope getScope() {
        return scope;
    }

    @Override
    public Environment.PlcObject visit(Ast.Source ast) {
        for(Ast.Field f : ast.getFields()){
            visit(f);
        }
        for(Ast.Method m : ast.getMethods()){
            visit(m);
        }
        return scope.lookupFunction("main", 0).invoke(new ArrayList<>());

        //throw new UnsupportedOperationException(); //TODO
    }

    @Override
    public Environment.PlcObject visit(Ast.Field ast) {
        if(!ast.getValue().isPresent()) {
            scope.defineVariable(ast.getName(), Environment.NIL);
        }
        else {
            scope.defineVariable(ast.getName(), visit(ast.getValue().get()));
        }
        return Environment.NIL;
        //throw new UnsupportedOperationException(); //TODO
    }

    @Override
    public Environment.PlcObject visit(Ast.Method ast) {

        scope.defineFunction(ast.getName(), ast.getParameters().size(), args -> {
            Scope originalScope = scope;
            scope = new Scope(scope);
            int i = 0;
            for(String param : ast.getParameters()){
                scope.defineVariable(param, args.get(i));
                i++;
            }
            try {
                for (Ast.Stmt stmt : ast.getStatements()) {
                    visit(stmt);
                }
            } catch(Return e){
                return e.value;
            }
            finally{
                scope = originalScope;
            }
            return Environment.NIL;
        });

        return Environment.NIL;
        //throw new UnsupportedOperationException(); //TODO
    }

    @Override
    public Environment.PlcObject visit(Ast.Stmt.Expression ast) {
        visit(ast.getExpression());
        return Environment.NIL;
        //throw new UnsupportedOperationException(); //TODO
    }

    @Override
    public Environment.PlcObject visit(Ast.Stmt.Declaration ast) {
        if (ast.getValue().isPresent()) {
            scope.defineVariable(ast.getName(), visit(ast.getValue().get()));
        }
        else {
            scope.defineVariable(ast.getName(), Environment.NIL);
        }

        return Environment.NIL;
        //throw new UnsupportedOperationException(); //TODO (in lecture)
    }

    @Override
    public Environment.PlcObject visit(Ast.Stmt.Assignment ast) {
        Ast.Expr.Access exprAccess = (Ast.Expr.Access) ast.getReceiver();
        Environment.PlcObject rec = null;

        if(exprAccess.getReceiver().equals(Optional.empty())) {
            scope.lookupVariable(exprAccess.getName()).setValue(visit(ast.getValue()));
            return Environment.NIL;
        }
        if (exprAccess.getReceiver().isPresent()) {
            rec = visit(exprAccess.getReceiver().get());
            rec.setField(exprAccess.getName(), visit(ast.getValue()));
        }

        return Environment.NIL;
    }

    @Override
    public Environment.PlcObject visit(Ast.Stmt.If ast) {
        List<Ast.Stmt> getStatements;
        Environment.PlcObject condition = visit(ast.getCondition());

        if (requireType(Boolean.class, condition)) {
            if (!ast.getThenStatements().isEmpty()) {
                getStatements = ast.getThenStatements();
                try {
                    scope = new Scope(scope);
                    for (Ast.Stmt stmt : getStatements) {
                        visit(stmt);
                    }
                }
                catch(Return e){
                    return e.value;
                }
                finally {
                    scope = scope.getParent();
                    return Environment.NIL;
                }
            }
            else {
                throw new RuntimeException("Empty Then Statements");
            }
        }
        else {
            if (!ast.getElseStatements().isEmpty()) {
                getStatements = ast.getElseStatements();
                try {
                    scope = new Scope(scope);
                    for (Ast.Stmt stmt : getStatements) {
                        visit(stmt);
                    }
                }
                catch(Return e){
                    return e.value;
                }
                finally {
                    scope = scope.getParent();
                    return Environment.NIL;
                }
            }
            else {
                return Environment.NIL; //Else statement is not required, no error if it is empty
            }
        }
        //throw new UnsupportedOperationException(); //TODO
    }

    @Override
    public Environment.PlcObject visit(Ast.Stmt.For ast) {
        String myName = ast.getName();
        List<Ast.Stmt> stmts = ast.getStatements();
        for(Object i : requireType(Iterable.class, visit(ast.getValue()) )){
            try{
                scope = new Scope(scope);
                scope.defineVariable(myName, (Environment.PlcObject) i);
                for(Ast.Stmt statement : stmts){
                    visit(statement);
                }
            }
            catch(Return e){
                return e.value;
            }
            finally{
                scope = scope.getParent();
            }
        }

        return Environment.NIL;
        //throw new UnsupportedOperationException(); //TODO
    }

    @Override
    public Environment.PlcObject visit(Ast.Stmt.While ast) {
        while (requireType(Boolean.class, visit(ast.getCondition()))) {
            try {
                scope = new Scope(scope);
                for (Ast.Stmt stmt : ast.getStatements()) {
                    visit(stmt);
                }
            }
            catch(Return e){
                return e.value;
            }
            finally {
                scope = scope.getParent();
            }
        }

        return Environment.NIL;
        //throw new UnsupportedOperationException(); //TODO (in lecture)
    }

    @Override
    public Environment.PlcObject visit(Ast.Stmt.Return ast) {
        throw new Return(visit(ast.getValue()));
        //throw new UnsupportedOperationException(); //TODO
    }

    @Override
    public Environment.PlcObject visit(Ast.Expr.Literal ast) {
        return ast.getLiteral() == null ? Environment.NIL : Environment.create(ast.getLiteral());
        //throw new UnsupportedOperationException(); //TODO
    }

    @Override
    public Environment.PlcObject visit(Ast.Expr.Group ast) {
        return visit(ast.getExpression());
        //throw new UnsupportedOperationException(); //TODO
    }

    @Override
    public Environment.PlcObject visit(Ast.Expr.Binary ast) {
        String op = ast.getOperator();
        Ast.Expr.Access empty = new Ast.Expr.Access(Optional.empty(), "undefined");
        Environment.PlcObject left = null;
        Environment.PlcObject right = null;

        if (!ast.getLeft().equals(empty)) {
            left = visit(ast.getLeft());
        }
        if (!ast.getRight().equals(empty)) {
            right = visit(ast.getRight());
        }

        if(op.equals("AND") || op.equals("OR")) {
            return op.equals("AND") ? Environment.create(requireType(Boolean.class, left) && requireType(Boolean.class, right))
                    : Environment.create(requireType(Boolean.class, left) || requireType(Boolean.class, right));
        }
        else if (op.equals("<") || op.equals("<=") || op.equals(">=") || op.equals(">")) {
            Comparable l = requireType(Comparable.class, left);
            Comparable r = requireType(Comparable.class, right);

            return (op.equals("<") || op.equals("<=")) ?
                    (op.equals("<") ? Environment.create(l.compareTo(r) < 0) : Environment.create(l.compareTo(r) <= 0)) :
                    (op.equals(">=") ? Environment.create(l.compareTo(r) >= 0) : Environment.create(l.compareTo(r) > 0));

            /*if (op.equals("<")) {
                return Environment.create(l.compareTo(r) < 0);
            }
            else if (op.equals("<=")) {
                return Environment.create(l.compareTo(r) <= 0);
            }
            else if (op.equals(">=")) {
                return Environment.create(l.compareTo(r) >= 0);
            }
            else {
                return Environment.create(l.compareTo(r) > 0);
            }*/
        }
        else if (op.equals("==") || op.equals("!=")) {
            return op.equals("==") ? Environment.create(left.equals(right)) : Environment.create(!left.equals(right));
        }
        else if(op.equals("+") || op.equals("-") || op.equals("*") || op.equals("/")) {
            if (op.equals("+")) {
                if (left.getValue().getClass().equals(String.class) ||
                        right.getValue().getClass().equals(String.class)) {
                    return Environment.create(left.getValue().toString() + right.getValue().toString());
                }
                else if (left.getValue().getClass().equals(BigInteger.class)) {
                    if (right.getValue().getClass().equals(BigInteger.class)) {
                        return Environment.create(((BigInteger) left.getValue()).add((BigInteger) right.getValue()));
                    }
                    throw new RuntimeException("Right operand must be an integer");
                }
                else if (left.getValue().getClass().equals(BigDecimal.class)) {
                    if (right.getValue().getClass().equals(BigDecimal.class)) {
                        return Environment.create(((BigDecimal) left.getValue()).add((BigDecimal) right.getValue()));
                    }
                    throw new RuntimeException("Right operand must be a decimal");
                }
            }
            else if (op.equals("-")) {
                if (left.getValue().getClass().equals(BigInteger.class)) {
                    if (right.getValue().getClass().equals(BigInteger.class)) {
                        return Environment.create(((BigInteger) left.getValue()).subtract((BigInteger) right.getValue()));
                    }
                    throw new RuntimeException("Right operand must be an integer");
                }
                else if (left.getValue().getClass().equals(BigDecimal.class)) {
                    if (right.getValue().getClass().equals(BigDecimal.class)) {
                        return Environment.create(((BigDecimal) left.getValue()).subtract((BigDecimal) right.getValue()));
                    }
                    throw new RuntimeException("Right operand must be a decimal");
                }
            }
            else if (op.equals("*")) {
                if (left.getValue().getClass().equals(BigInteger.class)) {
                    if (right.getValue().getClass().equals(BigInteger.class)) {
                        return Environment.create(((BigInteger) left.getValue()).multiply((BigInteger) right.getValue()));
                    }
                    throw new RuntimeException("Right operand must be an integer");
                }
                else if (left.getValue().getClass().equals(BigDecimal.class)) {
                    if (right.getValue().getClass().equals(BigDecimal.class)) {
                        return Environment.create(((BigDecimal) left.getValue()).multiply((BigDecimal) right.getValue()));
                    }
                    throw new RuntimeException("Right operand must be a decimal");
                }
            }
            else if (op.equals("/")) {
                if (left.getValue().getClass().equals(BigInteger.class)) {
                    if (right.getValue().getClass().equals(BigInteger.class)) {
                        return Environment.create(((BigInteger) left.getValue()).divide((BigInteger) right.getValue()));
                    }
                    throw new RuntimeException("Right operand must be an integer");
                }
                else if (left.getValue().getClass().equals(BigDecimal.class)) {
                    if (right.getValue().getClass().equals(BigDecimal.class)) {
                        return Environment.create(((BigDecimal) left.getValue()).divide((BigDecimal) right.getValue(), 1, RoundingMode.HALF_UP));
                    }
                    throw new RuntimeException("Right operand must be a decimal");
                }
            }
        }
        throw new RuntimeException("Error in Ast.Expr.Binary");
        //throw new UnsupportedOperationException(); //TODO
    }

    @Override
    public Environment.PlcObject visit(Ast.Expr.Access ast) {
        Environment.PlcObject rec = null;
        if (ast.getReceiver().isPresent()) {
            rec = visit(ast.getReceiver().get());
        }
        return !ast.getReceiver().equals(Optional.empty()) ? rec.getField(ast.getName()).getValue() :
                scope.lookupVariable(ast.getName()).getValue();
        //throw new UnsupportedOperationException(); //TODO
    }

    @Override
    public Environment.PlcObject visit(Ast.Expr.Function ast) {
        List<Environment.PlcObject> args = new ArrayList<>();
        Environment.PlcObject rec = null;
        Environment.Function func = null;
        List<Ast.Expr> getArgs;

        if (!ast.getArguments().isEmpty()) {
            getArgs = ast.getArguments();
            for(Ast.Expr argument : getArgs) {
                args.add(visit(argument));
            }
        }
        if(ast.getReceiver().equals(Optional.empty())) {
            func = scope.lookupFunction(ast.getName(), ast.getArguments().size());
            return func.invoke(args);
        }
        else if (ast.getReceiver().isPresent()) {
            rec = visit(ast.getReceiver().get());
        }
        return rec.callMethod(ast.getName(), args);
        //throw new UnsupportedOperationException(); //TODO
    }

    /**
     * Helper function to ensure an object is of the appropriate type.
     */
    private static <T> T requireType(Class<T> type, Environment.PlcObject object) {
        if (type.isInstance(object.getValue())) {
            return type.cast(object.getValue());
        } else {
            throw new RuntimeException("Expected type " + type.getName() + ", received " + object.getValue().getClass().getName() + "."); //TODO
        }
    }

    /**
     * Exception class for returning values.
     */
    private static class Return extends RuntimeException {

        private final Environment.PlcObject value;

        private Return(Environment.PlcObject value) {
            this.value = value;
        }

    }

}
