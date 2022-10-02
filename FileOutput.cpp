#include "RPManager.h"

char RandomProc4Console(int, int);
void setConsoleColor(char, char);
bool setTextColor(int);

struct cText
{
    string plain;
    vector<int> color;
};
class colorSX
{
public:
    int queryColor(const char* data)
    {
        for (int i = 0; i < 7; i++)
        {
            if (!_strnicmp(this->colorMap[i].index, data, 3))
            {
                return this->colorMap[i].data;
            }
        }
        return 0;
    }
private:
    struct cmap
    {
        char index[4];
        int data;
    };
    // map
    const cmap colorMap[8] =
    {
        {"whi",0},
        {"red",1},
        {"gre",2},
        {"blu",3},
        {"yel",4},
        {"pur",5},
        {"cya",6},
        {"rnd",7}
    };
};

extern bool outputLine(cText input)
{
    int i;
    for (i = 0; i < input.plain.length(); i++)
    {
        if (input.color[i] == -1)
        {
            setConsoleColor(ESC_CONSOLE_COLOR_BLACK, ESC_CONSOLE_COLOR_RED);
            setTextColor(ESC_COLOR_BLUE);
            cerr << "Error when attempt to solve the file!\n";
            setTextColor(ESC_COLOR_PUREWHITE);
            return true;
        }
        if (input.color[i] != 255)
        {
            setTextColor(input.color[i]);
        }
        printf("%c", input.plain[i]);
    }
    for (; i < input.color.size(); i++)
    {
        if (input.color[i] != 255)
        {
            setTextColor(input.color[i]);
        }
    }
    return false;
}
cText outputWFModifiersProcess(char* input)
{
    cText res;
    string ans;
    string tmp;
    colorSX control;
    for (int i = 0; i < strlen(input); i++)
    {
        tmp = "";
        //check modifers
        if (input[i] == '\\')
        {
            ++i;
            switch (input[i])
            {
            case 'n':
                ans += '\n';
                break;
            case 'a':
                ans += '\a';
                break;
            case 'b':
                ans += '\b';
                break;
            case 'r':
                ans += '\r';
                break;
            case 't':
                ans += '\t';
                break;
            case 'c':
                for (int j = 0; j < 3; j++)
                {
                    ++i;
                    tmp += input[i];
                }
                if (res.color.empty() || res.color[res.color.size() - 1] == 255)
                {
                    res.color.push_back(control.queryColor(tmp.c_str()));
                }
                else
                {
                    res.color[res.color.size() - 1] = control.queryColor(tmp.c_str());
                }
                continue;
            case '\\':
                ans += '\\';
                break;
                // wrong input
            default:
                ans += '?';
                break;
            }
            res.color.push_back(255);
            continue;
        }
        ans += input[i];
        res.color.push_back(255);
    }
    res.plain = ans;
    return res;
}

/// <summary>
/// output a with-format text file, MAY NOT WORK WITH ios::sync_with_stdio(0)
/// </summary>
/// <param name="filePath">path of the file</param>
/// <param name="lnFrom">from which line(use 0 as the head of the file)</param>
/// <param name="lnTo">to which line(use -1 to the end of the file)</param>
/// <returns>Success? if it did it then return false</returns>
extern bool outputWF(string filePath, int lnFrom, int lnTo)
{
    // temporarily store the content of the file
    char buffer[_Esc_maxn];
    // store the output of the file
    string storage;
    // file process
    fstream fin;
    fin.open(filePath);
    if (fin.fail())
    {
        return true;
    }

    // read file
    int i;
    for (i = 0; i < lnFrom; i++)
    {
        fin.getline(buffer, _Esc_maxn);
        if (fin.eof())
        {
            fin.close();
            return true;
        }
    }

    // process file
    cText res;
    if (lnTo == -1)
    {
        // theres a problem when using fin.eof(), so I have to use
        // fin.peek == EOF.
        while (!(fin.peek() == EOF))
        {
            res.plain = "";
            res.color.clear();
            // input file
            fin.getline(buffer, _Esc_maxn);
            res = outputWFModifiersProcess(buffer);
            // output file
            outputLine(res);
            printf("\n");
        }
        fin.close();
    }
    else
    {
        for (; i < lnTo; i++)
        {
            if (fin.eof())
            {
                fin.close();
                return true;
            }
            res.plain = "";
            res.color.clear();
            // input file
            fin.getline(buffer, _Esc_maxn);
            res = outputWFModifiersProcess(buffer);
            // output file
            outputLine(res);
            printf("\n");
        }
    }

    return false;
}

/// <summary>
/// output a plain text file, MAY NOT WORK WITH ios::sync_with_stdio(0)
/// </summary>
/// <param name="filePath">path of the file</param>
/// <param name="lnFrom">from which line(use 0 as the head of the file)</param>
/// <param name="lnTo">to which line(use -1 to the end of the file)</param>
/// <returns>Success? if it did it then return false</returns>
extern bool outputNF(string filePath, int lnFrom, int lnTo)
{
    // temporarily store the content of the file
    char buffer[_Esc_maxn];
    // store the output of the file
    string storage;
    // file process
    fstream fin;
    fin.open(filePath);
    if (fin.fail())
    {
        return true;
    }

    // read file
    int i;
    for (i = 0; i < lnFrom; i++)
    {
        fin.getline(buffer, _Esc_maxn);
        if (fin.eof())
        {
            fin.close();
            return true;
        }
    }

    if (lnTo == -1)
    {
        // theres a problem when using fin.eof(), so I have to use
        // fin.peek == EOF.
        while (!(fin.peek() == EOF))
        {
            // i&o
            fin.getline(buffer, _Esc_maxn);
            puts(buffer);
        }
        fin.close();
    }
    else
    {
        for (; i < lnTo; i++)
        {
            if (fin.eof())
            {
                fin.close();
                return true;
            }
            // i&o
            fin.getline(buffer, _Esc_maxn);
            puts(buffer);
        }
    }

    return false;
}
