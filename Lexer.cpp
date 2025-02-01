#include <bits/stdc++.h>
using namespace std;

struct trio
{
    int state;
    int lastState;
    int index;
};
trio make_trio(int _state,int _lastState,int _index)
{
    trio tr;
    tr.index = _index;
    tr.state = _state;
    tr.lastState = _lastState;
    return tr;
}

class AllSets
{
    set<char> _S;                   ///     _S = a|b|...|z|A|B|....|Z|_
    set<char> _N;                   ///     _N = 0|1|...|9
    set<char> _C;                   ///     _C = "
    set<char> _A;                   ///     _A = all printable ASCII chars
    set<char> _D;                   ///     _D = .
    set<char> _W;                   ///     _W = \n|\t|<space>|\0
    map<string,string> _KEY;        ///     ALL keywords
    map<string,string> _PUNC;       ///     ALL Punctuates
    map<string,string> _OP;         ///     ALL Operators

public:

    AllSets()
    {
        ///     _S = a|b|...|z|A|B|....|Z|_
        for(int i='A'; i<='Z'; i++)   _S.insert((char)i);
        for(int i='a'; i<='z'; i++)   _S.insert((char)i);
        _S.insert('_');


        ///     _N = 0|1|...|9
        for(int i='0'; i<='9'; i++)   _N.insert((char)i);


        ///     _C = "
        _C.insert('"');


        ///     _A = all printable ASCII chars
        for(int i=32; i<=126; i++) if(i != (int)'"')  _A.insert((char)i);


        ///     _D = .
        _D.insert('.');


        ///     _W = \n|\t|<space>|\0
        _W.insert(
        {
            '\n',
            '\t',
            ' ',
            '\0'
        });


        ///     _KEY = Allowed keywords in the language
        _KEY.insert(
        {
            make_pair("int","<INT-TYPE>"),
            make_pair("char","<CHAR-TYPE>"),
            make_pair("float","<FLOAT-TYPE>"),
            make_pair("double","<DOUBLE-TYPE>"),
            make_pair("string","<STRING-TYPE>"),
            make_pair("void","<VOID-TYPE>"),
            make_pair("signed","<TYPE-MODIFIER-SIGNED>"),
            make_pair("unsigned","<TYPE-MODIFIER-UNSIGNED>"),
            make_pair("if","<IF-CONDITION>"),
            make_pair("else","<ELSE-CONDITION>"),
            make_pair("switch","<SWITCH>"),
            make_pair("case","<CASE>"),
            make_pair("default","<DEFAULT>"),
            make_pair("for","<FOR-LOOP>"),
            make_pair("while","<WHILE-LOOP>"),
            make_pair("do","<DO-WHILE-LOOP>"),
            make_pair("break","<BREAK-CONTROL>"),
            make_pair("continue","<CONTINUE-CONTROL>"),
            make_pair("main","<MAIN>"),
            make_pair("return","<RETURN-CONTROL>"),
            make_pair("parallel","<PARALLEL>"),
            make_pair("fork", "<FORK>"),
            make_pair("join","<JOIN>"),
            make_pair("sync","<SYNC>"),
            make_pair("foreach","<FOREACH>"),
            make_pair("parallel", "<PARALLEL>"),
            make_pair("fork", "<FORK>"),
            make_pair("join", "<JOIN>"),
            make_pair("sync", "<SYNC>"),
            make_pair("foreach", "<FOREACH>"),
            make_pair("map", "<MAP>"),
            make_pair("shared", "<SHARED>"),
            make_pair("atomic", "<ATOMIC>"),
            make_pair("task", "<TASK>"),
            make_pair("schedule", "<SCHEDULE>"),
            make_pair("try", "<TRY>"),
            make_pair("catch", "<CATCH>"),
            make_pair("assert", "<ASSERT>"),
            make_pair("boolean", "<BOOLEAN-TYPE>"),
            make_pair("const", "<CONST>"),
            make_pair("var", "<VAR>"),
            make_pair("function", "<FUNCTION>"),
            make_pair("class", "<CLASS>"),
            make_pair("object", "<OBJECT>"),
            make_pair("this", "<THIS>"),
            make_pair("self", "<SELF>"),
            make_pair("public", "<PUBLIC>"),
            make_pair("private", "<PRIVATE>"),
            make_pair("protected", "<PROTECTED>"),
            make_pair("inheritance", "<INHERITANCE>"),
            make_pair("polymorphism", "<POLYMORPHISM>"),
            make_pair("new", "<NEW>"),
            make_pair("delete", "<DELETE>"),
            make_pair("input", "<INPUT>"),
            make_pair("output", "<OUTPUT>"),
            make_pair("error", "<ERROR>"),
            make_pair("performance", "<PERFORMANCE>"),
            make_pair("comment", "<COMMENT>"),
            make_pair("recursion", "<RECURSION>"),
            make_pair("enum", "<ENUM>"),
            make_pair("algorithm", "<ALGORITHM>"),
            make_pair("typeCasting", "<TYPE-CASTING>"),
            make_pair("method", "<METHOD>"),
            make_pair("static", "<STATIC>"),
            make_pair("let", "<LET>"),
            make_pair("func", "<FUNC>"),
            make_pair("elif", "<ELIF>"),
            make_pair("do", "<DO>"),
            make_pair("return", "<RETURN>"),
            make_pair("true", "<TRUE>"),
            make_pair("false", "<FALSE>"),
            make_pair("null", "<NULL>"),
            make_pair("undefined", "<UNDEFINED>"),
            make_pair("NaN", "<NAN>"),
            make_pair("Infinity", "<INFINITY>"),
            make_pair("package", "<PACKAGE>"),
            make_pair("import", "<IMPORT>"),
            make_pair("export", "<EXPORT>"),
            make_pair("module", "<MODULE>"),
            make_pair("interface", "<INTERFACE>"),
            make_pair("implements", "<IMPLEMENTS>"),
            make_pair("extends", "<EXTENDS>"),
            make_pair("super", "<SUPER>"),
            make_pair("constructor", "<CONSTRUCTOR>"),
            make_pair("destructor", "<DESTRUCTOR>"),
            make_pair("virtual", "<VIRTUAL>"),
            make_pair("override", "<OVERRIDE>"),
            make_pair("final", "<FINAL>"),
            make_pair("abstract", "<ABSTRACT>"),
            make_pair("namespace", "<NAMESPACE>"),
            make_pair("using", "<USING>"),
            make_pair("template", "<TEMPLATE>"),
            make_pair("typename", "<TYPENAME>"),
            make_pair("typedef", "<TYPEDEF>"),
            make_pair("struct", "<STRUCT>"),
            make_pair("union", "<UNION>"),
            make_pair("enum", "<ENUM>"),
            make_pair("goto", "<GOTO>"),
            make_pair("sizeof", "<SIZEOF>"),
            make_pair("alignof", "<ALIGNOF>"),
            make_pair("volatile", "<VOLATILE>"),
            make_pair("mutable", "<MUTABLE>"),
            make_pair("explicit", "<EXPLICIT>"),
            make_pair("friend", "<FRIEND>"),
            make_pair("operator", "<OPERATOR>"),
            make_pair("throw", "<THROW>"),
            make_pair("try", "<TRY>"),
            make_pair("catch", "<CATCH>"),
            make_pair("noexcept", "<NOEXCEPT>"),
            make_pair("static_assert", "<STATIC_ASSERT>"),
            make_pair("decltype", "<DECLTYPE>"),
            make_pair("auto", "<AUTO>"),
            make_pair("constexpr", "<CONSTEXPR>"),
            make_pair("thread_local", "<THREAD_LOCAL>"),
            make_pair("alignas", "<ALIGNAS>"),
            make_pair("char8_t", "<CHAR8_T>"),
            make_pair("char16_t", "<CHAR16_T>"),
            make_pair("char32_t", "<CHAR32_T>"),
            make_pair("wchar_t", "<WCHAR_T>"),
            make_pair("concept", "<CONCEPT>"),
            make_pair("requires", "<REQUIRES>"),
            make_pair("co_await", "<CO_AWAIT>"),
            make_pair("co_return", "<CO_RETURN>"),
            make_pair("co_yield", "<CO_YIELD>"),
            make_pair("reflexpr", "<REFLEXPR>"),
            make_pair("std", "<STD>"),
            make_pair("vector", "<VECTOR>"),
            make_pair("list", "<LIST>"),
            make_pair("map", "<MAP>"),
            make_pair("set", "<SET>"),
            make_pair("unordered_map", "<UNORDERED_MAP>"),
            make_pair("unordered_set", "<UNORDERED_SET>"),
            make_pair("queue", "<QUEUE>"),
            make_pair("stack", "<STACK>"),
            make_pair("deque", "<DEQUE>"),
            make_pair("priority_queue", "<PRIORITY_QUEUE>"),
            make_pair("pair", "<PAIR>"),
            make_pair("tuple", "<TUPLE>"),
            make_pair("optional", "<OPTIONAL>"),
            make_pair("variant", "<VARIANT>"),
            make_pair("any", "<ANY>"),
            make_pair("function", "<FUNCTION>"),
            make_pair("bind", "<BIND>"),
            make_pair("mem_fn", "<MEM_FN>"),
            make_pair("reference_wrapper", "<REFERENCE_WRAPPER>"),
            make_pair("shared_ptr", "<SHARED_PTR>"),
            make_pair("unique_ptr", "<UNIQUE_PTR>"),
            make_pair("weak_ptr", "<WEAK_PTR>"),
            make_pair("make_shared", "<MAKE_SHARED>"),
            make_pair("make_unique", "<MAKE_UNIQUE>"),
            make_pair("allocator", "<ALLOCATOR>"),
            make_pair("iterator", "<ITERATOR>"),
            make_pair("const_iterator", "<CONST_ITERATOR>"),
            make_pair("reverse_iterator", "<REVERSE_ITERATOR>"),
            make_pair("move", "<MOVE>"),
            make_pair("forward", "<FORWARD>"),
            make_pair("swap", "<SWAP>"),
            make_pair("begin", "<BEGIN>"),
            make_pair("end", "<END>"),
            make_pair("cbegin", "<CBEGIN>"),
            make_pair("cend", "<CEND>"),
            make_pair("rbegin", "<RBEGIN>"),
            make_pair("rend", "<REND>"),
            make_pair("crbegin", "<CRBEGIN>"),
            make_pair("crend", "<CREND>"),
            make_pair("size", "<SIZE>"),
            make_pair("empty", "<EMPTY>"),
            make_pair("max_size", "<MAX_SIZE>"),
            make_pair("capacity", "<CAPACITY>"),
            make_pair("reserve", "<RESERVE>"),
            make_pair("shrink_to_fit", "<SHRINK_TO_FIT>"),
            make_pair("clear", "<CLEAR>"),
            make_pair("insert", "<INSERT>"),
            make_pair("emplace", "<EMPLACE>"),
            make_pair("erase", "<ERASE>"),
            make_pair("push_back", "<PUSH_BACK>"),
            make_pair("pop_back", "<POP_BACK>"),
            make_pair("push_front", "<PUSH_FRONT>"),
            make_pair("pop_front", "<POP_FRONT>"),
            make_pair("resize", "<RESIZE>"),
            make_pair("assign", "<ASSIGN>"),
            make_pair("get_allocator", "<GET_ALLOCATOR>"),
            make_pair("data", "<DATA>"),
            make_pair("at", "<AT>"),
            make_pair("front", "<FRONT>"),
            make_pair("back", "<BACK>"),
            make_pair("find", "<FIND>"),
            make_pair("count", "<COUNT>"),
            make_pair("lower_bound", "<LOWER_BOUND>"),
            make_pair("upper_bound", "<UPPER_BOUND>"),
            make_pair("equal_range", "<EQUAL_RANGE>"),
            make_pair("binary_search", "<BINARY_SEARCH>"),
            make_pair("merge", "<MERGE>"),
            make_pair("sort", "<SORT>"),
            make_pair("stable_sort", "<STABLE_SORT>"),
            make_pair("partial_sort", "<PARTIAL_SORT>"),
            make_pair("nth_element", "<NTH_ELEMENT>"),
            make_pair("make_heap", "<MAKE_HEAP>"),
            make_pair("push_heap", "<PUSH_HEAP>"),
            make_pair("pop_heap", "<POP_HEAP>"),
            make_pair("sort_heap", "<SORT_HEAP>"),
            make_pair("min", "<MIN>"),
            make_pair("max", "<MAX>"),
            make_pair("minmax", "<MINMAX>"),
            make_pair("min_element", "<MIN_ELEMENT>"),
            make_pair("max_element", "<MAX_ELEMENT>"),
            make_pair("minmax_element", "<MINMAX_ELEMENT>"),
            make_pair("lexicographical_compare", "<LEXICOGRAPHICAL_COMPARE>"),
            make_pair("next_permutation", "<NEXT_PERMUTATION>"),
            make_pair("prev_permutation", "<PREV_PERMUTATION>"),
            make_pair("iota", "<IOTA>"),
            make_pair("accumulate", "<ACCUMULATE>"),
            make_pair("inner_product", "<INNER_PRODUCT>"),
            make_pair("adjacent_difference", "<ADJACENT_DIFFERENCE>"),
            make_pair("partial_sum", "<PARTIAL_SUM>"),
            make_pair("reduce", "<REDUCE>"),
            make_pair("transform_reduce", "<TRANSFORM_REDUCE>"),
            make_pair("inclusive_scan", "<INCLUSIVE_SCAN>"),
            make_pair("exclusive_scan", "<EXCLUSIVE_SCAN>"),
            make_pair("transform_inclusive_scan", "<TRANSFORM_INCLUSIVE_SCAN>"),
            make_pair("transform_exclusive_scan", "<TRANSFORM_EXCLUSIVE_SCAN>"),
            make_pair("sample", "<SAMPLE>"),
            make_pair("shuffle", "<SHUFFLE>"),
            make_pair("for_each", "<FOR_EACH>"),
            make_pair("for_each_n", "<FOR_EACH_N>"),
            make_pair("all_of", "<ALL_OF>"),
            make_pair("any_of", "<ANY_OF>"),
            make_pair("none_of", "<NONE_OF>"),
            make_pair("copy", "<COPY>"),
            make_pair("copy_if", "<COPY_IF>"),
            make_pair("copy_n", "<COPY_N>"),
            make_pair("copy_backward", "<COPY_BACKWARD>"),
            make_pair("move", "<MOVE>"),
            make_pair("move_backward", "<MOVE_BACKWARD>"),
            make_pair("fill", "<FILL>"),
            make_pair("fill_n", "<FILL_N>"),
            make_pair("transform", "<TRANSFORM>"),
            make_pair("generate", "<GENERATE>"),
            make_pair("generate_n", "<GENERATE_N>"),
            make_pair("remove", "<REMOVE>"),
            make_pair("remove_if", "<REMOVE_IF>"),
            make_pair("remove_copy", "<REMOVE_COPY>"),
            make_pair("remove_copy_if", "<REMOVE_COPY_IF>"),
            make_pair("replace", "<REPLACE>"),
            make_pair("replace_if", "<REPLACE_IF>"),
            make_pair("replace_copy", "<REPLACE_COPY>"),
            make_pair("replace_copy_if", "<REPLACE_COPY_IF>"),
            make_pair("swap_ranges", "<SWAP_RANGES>"),
            make_pair("reverse", "<REVERSE>"),
            make_pair("reverse_copy", "<REVERSE_COPY>"),
            make_pair("rotate", "<ROTATE>"),
            make_pair("rotate_copy", "<ROTATE_COPY>"),
            make_pair("shift_left", "<SHIFT_LEFT>"),
            make_pair("shift_right", "<SHIFT_RIGHT>"),
            make_pair("unique", "<UNIQUE>"),
            make_pair("unique_copy", "<UNIQUE_COPY>"),
            make_pair("is_partitioned", "<IS_PARTITIONED>"),
            make_pair("partition", "<PARTITION>"),
            make_pair("partition_copy", "<PARTITION_COPY>"),
            make_pair("stable_partition", "<STABLE_PARTITION>"),
            make_pair("partition_point", "<PARTITION_POINT>"),
            make_pair("is_sorted", "<IS_SORTED>"),
            make_pair("is_sorted_until", "<IS_SORTED_UNTIL>"),
            make_pair("is_heap", "<IS_HEAP>"),
            make_pair("is_heap_until", "<IS_HEAP_UNTIL>"),
            make_pair("clamp", "<CLAMP>"),
            make_pair("is_permutation", "<IS_PERMUTATION>"),
            make_pair("next", "<NEXT>"),
            make_pair("prev", "<PREV>"),
            make_pair("distance", "<DISTANCE>"),
            make_pair("advance", "<ADVANCE>"),
            make_pair("iter_swap", "<ITER_SWAP>"),
            make_pair("begin", "<BEGIN>"),
            make_pair("end", "<END>"),
            make_pair("cbegin", "<CBEGIN>"),
            make_pair("cend", "<CEND>"),
            make_pair("rbegin", "<RBEGIN>"),
            make_pair("rend", "<REND>"),
            make_pair("crbegin", "<CRBEGIN>"),
            make_pair("crend", "<CREND>"),
            make_pair("size", "<SIZE>"),
            make_pair("empty", "<EMPTY>"),
            make_pair("max_size", "<MAX_SIZE>"),
            make_pair("capacity", "<CAPACITY>"),
            make_pair("reserve", "<RESERVE>"),
            make_pair("shrink_to_fit", "<SHRINK_TO_FIT>"),
            make_pair("clear", "<CLEAR>"),
            make_pair("insert", "<INSERT>"),
            make_pair("emplace", "<EMPLACE>"),
            make_pair("erase", "<ERASE>"),
            make_pair("push_back", "<PUSH_BACK>"),
            make_pair("pop_back", "<POP_BACK>"),
            make_pair("push_front", "<PUSH_FRONT>"),
            make_pair("pop_front", "<POP_FRONT>"),
            make_pair("resize", "<RESIZE>"),
            make_pair("assign", "<ASSIGN>"),
            make_pair("get_allocator", "<GET_ALLOCATOR>"),
            make_pair("data", "<DATA>"),
            make_pair("at", "<AT>"),
            make_pair("front", "<FRONT>"),
            make_pair("back", "<BACK>"),
            make_pair("find", "<FIND>"),
            make_pair("count", "<COUNT>"),
        });


        ///     _PUNC = All punctuates
        _PUNC.insert(
        {
            make_pair("[","<[>"),
            make_pair("]","<]>"),
            make_pair("(","<(>"),
            make_pair(")","<)>"),
            make_pair("{","<{>"),
            make_pair("}","<}>"),
            //make_pair("'","<'>"),
            make_pair(".","<.>"),
            make_pair(",","<,>"),
            make_pair(":","<:>"),
            make_pair("~","<ERROR LEXEME>"),
            make_pair("_","<ERROR LEXEME>"),
            make_pair("`","<ERROR LEXEME>"),
            make_pair("$","<ERROR LEXEME>"),
            make_pair("@","<ERROR LEXEME>"),
            make_pair("?","<?>"),
            make_pair(" ","<SPACE>"),
            make_pair(";","<;>"),
            make_pair("#","<#>")
        });


        ///     _OP = All operators
        _OP.insert(
        {
            make_pair("+","<ARITH-ADD-OP>"),
            make_pair("-","<ARITH-SUB-OP>"),
            make_pair("*","<ARITH-MUL-OP>"),
            make_pair("/","<ARITH-DIV-OP>"),
            make_pair("%","<ARITH-MOD-OP>"),

            make_pair("<","<RELAT-LESS-OP>"),
            make_pair("<=","<RELAT-LESS-EQUAL-OP>"),
            make_pair(">=","<RELAT-GREAT-EQUAL-OP>"),
            make_pair(">","<RELAT-GREAT-OP>"),
            make_pair("==","<RELAT-EQUAL-OP>"),
            make_pair("!=","<RELAT-NOT-EQUAL-OP>"),

            make_pair("&&","<LOGIC-AND-OP>"),
            make_pair("||","<LOGIC-OR-OP>"),
            make_pair("!","<LOGIC-NOT-OP>"),

            make_pair("&","<BIT-AND-OP>"),
            make_pair("|","<BIT-OR-OP>"),
            make_pair("^","<BIT-XOR-OP>"),
            make_pair("<<","<BIT-SHLEFT-OP>"),
            make_pair(">>","<BIT-SHRIGHT-OP>"),


            make_pair("=","<ASN-OP>"),
            make_pair("%=","<ASN-MOD-OP>"),
            make_pair("/=","<ASN-DIV-OP>"),
            make_pair("*=","<ASN-MUL-OP>"),
            make_pair("+=","<ASN-ADD-OP>"),
            make_pair("-=","<ASN-SUB-OP>"),
            make_pair("++","<ASN-INC-OP>"),
            make_pair("--","<ASN-DEC-OP>"),
        });

    }

    bool S(char c)
    {
        return(_S.find(c) == _S.end()?false:true);
    }
    bool N(char c)
    {
        return(_N.find(c) == _N.end()?false:true);
    }
    bool C(char c)
    {
        return(_C.find(c) == _C.end()?false:true);
    }
    bool A(char c)
    {
        return(_A.find(c) == _A.end()?false:true);
    }
    bool D(char c)
    {
        return(_D.find(c) == _D.end()?false:true);
    }
    bool W(char c)
    {
        return(_W.find(c) == _W.end()?false:true);
    }
    string Key(string c)
    {
        return(_KEY.find(c) == _KEY.end()?"NULL":_KEY[c]);
    }
    string Punc(string c)
    {
        return(_PUNC.find(c) == _PUNC.end()?"NULL":_PUNC[c]);
    }
    string Op(string c)
    {
        return(_OP.find(c) == _OP.end()?"NULL":_OP[c]);
    }

} Set;

class DFA
{

    map<int, string> descState;
    vector<string> tokens;
public:
    DFA()
    {
        descState.insert(
        {
            make_pair(7, "<STRING>"),
            make_pair(2, "<ID>"),
            make_pair(8, "<ERROR-Ending Double quote Expected>"),
            make_pair(3, "<ERROR-Ending Double quote Expected>"),
            make_pair(4, "<ERROR-Real Number error>"),
            make_pair(5, "<ID>"),
            make_pair(6, "<ID>"),
            make_pair(1, "<NUM>"),
            make_pair(9, "<NUM-FLOATING>"),
            make_pair(10, "<ERROR>"),
            make_pair(11, "<ERROR>"),
            make_pair(12, "<ERROR-Multi char>"),
            make_pair(13, "<CHAR>")
        });

    }

    trio check(string str)
    {
        int state=0, lastState=0, i = 0;

        while(true)
        {
            switch(state)
            {
            case 0:
                if(Set.S(str[i]))
                {
                    state = 2;
                    lastState = 0;
                }
                else if(Set.N(str[i]))
                {
                    state = 1;
                    lastState = 0;
                }
                else if(Set.C(str[i]))
                {
                    state = 3;
                    lastState = 0;
                }
                else if(str[i] == '\'')
                {
                    state = 11;
                    lastState = 0;
                }
                else
                {
                    lastState = 0;
                    state = 10;
                }
                break;
            case 1:
                if(Set.N(str[i]))
                {
                    state = 1;
                    lastState = 1;
                }
                else if(Set.D(str[i]))
                {
                    state = 4;
                    lastState = 1;
                }
                else
                {
                    lastState = 1;
                    state = 10;
                }
                break;
            case 4:
                if(Set.N(str[i]))
                {
                    state = 9;
                    lastState = 4;
                }
                else
                {
                    lastState = 4;
                    state = 10;
                }
                break;
            case 9:
                if(Set.N(str[i]))
                {
                    state = 9;
                    lastState = 9;
                }
                else
                {
                    lastState = 9;
                    state = 10;
                }
                break;
            case 2:
                if(Set.N(str[i]))
                {
                    state = 5;
                    lastState = 2;
                }
                else if(Set.S(str[i]))
                {
                    state = 6;
                    lastState = 2;
                }
                else
                {
                    lastState = 2;
                    state = 10;
                }
                break;
            case 5:
                if(Set.N(str[i]))
                {
                    state = 5;
                    lastState = 5;
                }
                else if(Set.S(str[i]))
                {
                    state = 6;
                    lastState = 5;
                }
                else
                {
                    lastState = 5;
                    state = 10;
                }
                break;
            case 6:
                if(Set.N(str[i]))
                {
                    state = 5;
                    lastState = 6;
                }
                else if(Set.S(str[i]))
                {
                    state = 6;
                    lastState = 6;
                }
                else
                {
                    lastState = 6;
                    state = 10;
                }
                break;
            case 3:
                if(Set.A(str[i]))
                {
                    state = 8;
                    lastState = 3;
                }
                else if(Set.C(str[i]))
                {
                    state = 7;
                    lastState = 3;
                }
                else
                {
                    lastState = 3;
                    state = 10;
                }
                break;
            case 8:
                if(Set.A(str[i]))
                {
                    state = 8;
                    lastState = 8;
                }
                else if(Set.C(str[i]))
                {
                    state = 7;
                    lastState = 8;
                }
                else
                {
                    lastState = 8;
                    state = 10;
                }
                break;
            case 7:
                lastState = 7;
                return make_trio(state,lastState,i);
                break;
            case 11:
                if(Set.A(str[i]) && str[i]!= '\'')
                {
                    state = 12;
                    lastState = 11;
                }
                else if(str[i] == '\'')
                {
                    state = 13;
                    lastState = 11;
                }
                else
                {
                    lastState = 11;
                    state = 10;
                }
                break;
            case 12:
                if(str[i] == '\'')
                {
                    state = 13;
                    lastState = 12;
                }
                else
                {
                    lastState = 12;
                    state = 10;
                }
                break;
            case 13:
                lastState = 13;
                return make_trio(state,lastState,i);
                break;
            case 10:
                i = i-1;
                return make_trio(state,lastState,i);
            }
            i++;
        }
        return make_trio(state,lastState,i);
    }

    string clrPrefix(string x)
    {
        int xLength = x.length();
        int xStart = 0;

        if(xLength > 1)
        {
            string tx = x.substr(0,2);
            string td = x.substr(0,1);

            if(Set.Punc(tx)!= "NULL")
            {
                tokens.push_back(tx);
                xStart = 2;
            }
            else if(Set.Op(tx)!= "NULL")
            {
                tokens.push_back(tx);
                xStart = 2;
            }
            else if(Set.Punc(td)!= "NULL")
            {
                tokens.push_back(td);
                xStart = 1;
            }
            else if(Set.Op(td)!= "NULL")
            {
                tokens.push_back(td);
                xStart = 1;
            }
        }
        else if(xLength == 1)
        {
            if(Set.Punc(x)!="NULL")
            {
                tokens.push_back(x);
                xStart = 1;
            }
            else if(Set.Op(x)!="NULL")
            {
                tokens.push_back(x);
                xStart = 1;
            }
        }
        string ret = x.substr(xStart,xLength-xStart);
        return ret;
    }

    string clrDfaPrefix(string words)
    {
        trio sample = check(words);
        //cout<<"Index: "<<sample.index<<endl<<"Last: "<<descState[sample.lastState]<<endl;

        /// The num/id/string part of the word is seperated
        string tok = words.substr(0,sample.index);

        /// Seperated part is pushed to Tokens
        tokens.push_back(tok);

        ///Remaining part is returned
        return words.substr(sample.index,words.size()-tok.size());
    }

    void wordsToTokens(string words)
    {
        while(!words.empty())
        {
            int wordLength = words.size();
            while(true)
            {
                words = clrPrefix(words);
                if(wordLength == words.size()) break;
                wordLength = words.size();
            }

            words = clrDfaPrefix(words);
        }
    }

    void trim(string& s)
    {
        size_t p = s.find_first_not_of(" \t");
        s.erase(0, p);

        p = s.find_last_not_of(" \t");
        if (string::npos != p)
            s.erase(p+1);
    }

    void detect(string buffer)
    {
        trim(buffer);
        wordsToTokens(buffer);

        /*
        stringstream ss(buffer);
        string words;

        while(ss>>words)
        {
            wordsToTokens(words);

            tokens.push_back(" ");
        }
        tokens.pop_back();
        */
    }

    vector<string> getTokens()
    {
        return tokens;
    }

    void addEndLine()
    {
        tokens.push_back("\n");
    }

    void printTokens()
    {
        cout<<"\n\n\n------------------------TOKENS------------------------\n";
        for(int i=0; i<tokens.size(); i++)
        {
            if(tokens[i] != "\0")
            {
                cout<<(tokens[i]=="\n"?"":tokens[i])<<"\t\t\t\t---->  "
                    <<describeToken(tokens[i])<<endl;
            }
        }
    }

    string describeToken(string token)
    {
        if(Set.Key(token) != "NULL")    return Set.Key(token);
        if(Set.Punc(token)!="NULL")     return Set.Punc(token);
        if(Set.Op(token)!="NULL")       return Set.Op(token);
        if(token == "\n")                   return "<ENDLINE>";

        return descState[check(token).lastState];

    }

} dfa;



int main()
{
    freopen("input.txt","r",stdin);
    //freopen("output.txt","w",stdout);


    string buffer;

    while(!cin.eof())
    {
        getline(cin, buffer);
        if(!buffer.empty())
        {
            dfa.detect(buffer);
            dfa.addEndLine();
        }
    }

    dfa.printTokens();

}
