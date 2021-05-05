package plc.project;

import java.io.PrintWriter;

public final class Generator implements Ast.Visitor<Void> {

    private final PrintWriter writer;
    private int indent = 0;

    public Generator(PrintWriter writer) {
        this.writer = writer;
    }

    private void print(Object... objects) {
        for (Object object : objects) {
            if (object instanceof Ast) {
                visit((Ast) object);
            } else {
                writer.write(object.toString());
            }
        }
    }

    private void newline(int indent) {
        writer.println();
        for (int i = 0; i < indent; i++) {
            writer.write("    ");
        }
    }

    @Override
    public Void visit(Ast.Source ast) {
        print("public class Main {");
        newline(0);
        indent++;
        for(int i = 0; i < ast.getFields().size(); i++){
            newline(indent);
            print(ast.getFields().get(i));
        }
        if(ast.getFields().size() > 0){
            newline(0);
        }
        newline(indent);
        print("public static void main(String[] args) {");
        newline(++indent);
        print("System.exit(new Main().main());");
        newline(--indent);
        print("}");
        newline(0);
        for(int j = 0; j < ast.getMethods().size(); j++){
            newline(indent);
            print(ast.getMethods().get(j));
            newline(0);
        }
        newline(--indent);
        print("}");
        //throw new UnsupportedOperationException(); //TODO
        return null;
    }

    @Override
    public Void visit(Ast.Field ast) {
        print(Environment.getType(ast.getTypeName()).getJvmName()," ",ast.getName());
        if(ast.getValue().isPresent()){
            print(" = ",ast.getValue().get());
        }
        print(";");
        //throw new UnsupportedOperationException(); //TODO
        return null;
    }

    @Override
    public Void visit(Ast.Method ast) {
        print(Environment.getType(ast.getReturnTypeName().get()).getJvmName()," ",ast.getName(),"(");
        for(int i = 0; i < ast.getParameters().size()-1; i++){
            print(Environment.getType(ast.getParameterTypeNames().get(i)).getJvmName()," ",ast.getParameters().get(i),", ");
        }
        if(ast.getParameters().size() > 0) {
            print(Environment.getType(ast.getParameterTypeNames().get(ast.getParameters().size())).getJvmName(), " ", ast.getParameters().get(ast.getParameters().size()));
        }
        print(") {");
        ++indent;
        for(int j = 0; j < ast.getStatements().size(); j++){
            newline(indent);
            print(ast.getStatements().get(j));
        }
        newline(--indent);
        print("}");
        //throw new UnsupportedOperationException(); //TODO
        return null;
    }

    @Override
    public Void visit(Ast.Stmt.Expression ast) {
        print(ast.getExpression(), ";");
        //throw new UnsupportedOperationException(); //TODO
        return null;
    }

    @Override
    public Void visit(Ast.Stmt.Declaration ast) {
        print(ast.getVariable().getType().getJvmName()," ",ast.getVariable().getName());
        if(ast.getValue().isPresent()){
            print(" = ",ast.getValue().get(),";");
        }
        else{
            print(";");
        }
        //throw new UnsupportedOperationException(); //TODO
        return null;
    }

    @Override
    public Void visit(Ast.Stmt.Assignment ast) {
        print(ast.getReceiver()," = ",ast.getValue(),";");
        //throw new UnsupportedOperationException(); //TODO
        return null;
    }

    @Override
    public Void visit(Ast.Stmt.If ast) {
        print("if (", ast.getCondition(), ") {");

        if (!ast.getThenStatements().isEmpty()) {
            newline(++indent);
            for (int i = 0; i < ast.getThenStatements().size(); i++) {
                if (i != 0) {
                    newline(indent);
                }
                print(ast.getThenStatements().get(i));
            }
            newline(--indent);
        }
        print("}");
        if (!ast.getElseStatements().isEmpty()) {
            print(" else {");
            newline(++indent);
            for (int i = 0; i < ast.getElseStatements().size(); i++) {
                if (i != 0) {
                    newline(indent);
                }
                print(ast.getElseStatements().get(i));
            }
            newline(--indent);
            print("}");
        }
        //throw new UnsupportedOperationException(); //TODO
        return null;
    }

    @Override
    public Void visit(Ast.Stmt.For ast) {
        print("for (", ast.getValue().getType(), " ", ast.getName(), " : ", ast.getValue(), ") {");

        if (!ast.getStatements().isEmpty()) {
            newline(++indent);
            for (int i = 0; i < ast.getStatements().size(); i++) {
                if (i != 0) {
                    newline(indent);
                }
                print(ast.getStatements().get(i));
            }
            newline(--indent);
        }
        print("}");
        //throw new UnsupportedOperationException(); //TODO
        return null;
    }

    @Override
    public Void visit(Ast.Stmt.While ast) {
        print("while (", ast.getCondition(), ") {");

        if (!ast.getStatements().isEmpty()) {
            newline(++indent);
            for (int i = 0; i < ast.getStatements().size(); i++) {
                if (i != 0) {
                    newline(indent);
                }
                print(ast.getStatements().get(i));
            }
            newline(--indent);
        }
        print("}");
        //throw new UnsupportedOperationException(); //TODO
        return null;
    }

    @Override
    public Void visit(Ast.Stmt.Return ast) {
        print("return ", ast.getValue(),";");
        //throw new UnsupportedOperationException(); //TODO
        return null;
    }

    @Override
    public Void visit(Ast.Expr.Literal ast) {
        switch(ast.getType().getName()){
            case "Character":
                print("\"",ast.getLiteral(),"\"");
                break;
            case "String":
                print("\"",ast.getLiteral(),"\"");
                break;
            default:
                print(ast.getLiteral());
        }
        //throw new UnsupportedOperationException(); //TODO
        return null;
    }

    @Override
    public Void visit(Ast.Expr.Group ast) {
        print("(", ast.getExpression(),")");
        //throw new UnsupportedOperationException(); //TODO
        return null;
    }

    @Override
    public Void visit(Ast.Expr.Binary ast) {
        visit(ast.getLeft());
        String operator;
        switch(ast.getOperator()){
            case "AND":
                operator = "&&";
                break;
            case "OR":
                operator = "||";
                break;
            default:
                operator = ast.getOperator();
                break;
        }
        print(" ",operator," ");
        visit(ast.getRight());
        //throw new UnsupportedOperationException(); //TODO
        return null;
    }

    @Override
    public Void visit(Ast.Expr.Access ast) {
        //ast.getName();ast.getVariable().getJvmName();
        print(ast.getVariable().getJvmName());
        //throw new UnsupportedOperationException(); //TODO
        return null;
    }

    @Override
    public Void visit(Ast.Expr.Function ast) {
        if(ast.getReceiver().isPresent()){
            print(ast.getReceiver().get(),".");
        }
        print(ast.getFunction().getJvmName(),"(");
        if(ast.getArguments().size() >= 1) {
            for (int a = 0; a < ast.getArguments().size() - 1; a++) {
                print(ast.getArguments().get(a), ", ");
            }
            print(ast.getArguments().get(ast.getArguments().size()-1));
        }
        print(")");
        //throw new UnsupportedOperationException(); //TODO
        return null;
    }

}
