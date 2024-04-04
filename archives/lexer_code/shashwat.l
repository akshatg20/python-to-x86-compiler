%{
    #include <iostream>   // For std::cout
    #include <string>     // For std::string
    #include <map> // For std::unordered_map
    #include <utility>    // For std::pair
    #include <cctype>     // For std::tolower

    using namespace std;

    int counter(string s,string typ);
    int addinvalid(string s,int linenumber,int charnumber,string err);
    int incrementline(string s);
    string getlowercase(string s,string typ);

    string invalid = "";
    int linenumber=1,  charnumber=1;
    map<string , string> mp; // store uppercase - type
    map<string, int> mp2; // store lowercase - count

%}

keywords         (False|await|else|import|pass|None|break|except|in|raise|True|class|finally|is|return|and|continue|for|lambda|try|as|def|from|nonlocal|while|assert|del|global|not|with|async|elif|if|or|yield)
 /* softkeywords     (match|case|type|\_) */

Lu              ([A-Z])
Ll              ([a-z])
Lm              ([\xAA\xBA])
Nd              ([0-9])
Pc              [\x95]

id_start        ({Lu}|{Ll}|{Lm}|[_])
id_continue     ({id_start}|{Nd}|{Pc}|[\xB7])
id              ({id_start}{id_continue}*)
rid_system      (\_\_{id}\_\_)
rid_classpvt    (\_\_{id})
rid_import      (\_{id})
rid__           (\_)


%%

{keywords}       {counter(yytext,"KEYWORD\t"); charnumber+=yyleng;}
 /* {softkeywords}   {counter(yytext,"SOFTKEYWORD\t"); charnumber+=yyleng;} */

{rid_system}     {counter(yytext,"RID_SYSTEM\t"); charnumber+=yyleng;}
{rid_classpvt}   {counter(yytext,"RID_CLASSPVT\t"); charnumber+=yyleng;}
{rid_import}     {counter(yytext,"RID_IMPORT\t"); charnumber+=yyleng;}
{rid__}          {counter(yytext,"RID__\t"); charnumber+=yyleng;}
{id}             {counter(yytext,"NAME\t"); charnumber+=yyleng;}
.                {counter(yytext,"ILLEGAL\t"); charnumber+=yyleng;}


%%

/* doubts with the following */
/* place _ in softkeywords OR rid__ */

int counter(string s,string typ)
{
    // identity
    if(mp.find(s)==mp.end())
    {
        mp[s]=typ;
    }

    // count
    if(mp2.find(s)!=mp2.end())
    {
        mp2[s]++;
    }
    else
    {
        mp2[s]=1;
    }
    
    return 0;
}

int yywrap()
{}

int main()
{

    yylex();

    std::cout << "Token" << "\t\t" << "Count" << "\t\t" << "Lexeme" << endl;
    for (const auto& entry : mp) 
    {
        const std::string& key = entry.first;
        const std::string& value1 = entry.second;
        int value2 = mp2[getlowercase(entry.first,entry.second)];

        std::cout << value1 << "\t" << value2 << "\t\t" << key << endl;
    }

    cout<<invalid<<endl;
}