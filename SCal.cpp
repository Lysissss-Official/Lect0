//
// Created by Niumo on 2025/10/25.
//
#include <bits/stdc++.h>

std::list<uint16_t> ex{0x0000, 0x0001};
std::list<uint16_t>::iterator pos;
std::string s;

void Oput(const std::list<uint16_t>& l)
{
    printf(">> Oput: ");
    for(auto it = l.begin(); it != l.end(); ++it)
    {
        if(*it >= 0 && *it <= 1)
        {
            printf("~");
        }
        if(*it >= '0' && *it <= '9' || *it == '+' || *it == '-' || *it == '*' || *it == '/' || *it == '^' || *it == '(' || *it == ')')
        {
            printf("%c", *it);
        }
        if(it == pos)
        {
            printf("|");
        }
    }
}

int16_t pri(uint16_t ch)
{
    if (ch == '^')
        return 2;
    if (ch == '*' || ch == '/')
        return 1;
    if (ch == '+' || ch == '-')
        return 0;
    if (ch == '(')
        return -1;
}

std::string L2S(const std::list<uint16_t>& l)
{
    std::string output;
    std::stack<uint16_t> st;
    bool lastWasOperator = true;  // 标记前一个字符是否是运算符（用于识别一元负号）
    bool lastWasDigit = false;

    // 跳过首尾的特殊标记
    auto start = ++l.begin();
    auto end = --l.end();

    for(auto it = start; it != end; ++it)
    {
        uint16_t ch = *it;

        // 处理数字
        if (ch >= '0' && ch <= '9')
        {
            if (!output.empty() && !lastWasDigit && output.back() != ' ')
                output += " ";
            output += ch;
            lastWasDigit = true;
            lastWasOperator = false;
        }
            // 处理一元负号（前面是运算符或开头）
        else if (ch == '-' && lastWasOperator)
        {
            // 将一元负号转换为特殊标记，比如 'n'
            if (!output.empty() && output.back() != ' ')
                output += " ";
            output += "0 ";  // 添加0，然后减去后面的数字
            st.push('-');
            lastWasDigit = false;
            lastWasOperator = true;
        }
            // 处理运算符和括号
        else if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '(' || ch == ')')
        {
            lastWasDigit = false;

            if (ch == '(')
            {
                st.push(ch);
                lastWasOperator = true;  // 左括号后可能是一元运算符
            }
            else if (ch == ')')
            {
                if (!output.empty() && output.back() != ' ')
                    output += " ";

                while (!st.empty() && st.top() != '(')
                {
                    output += st.top();
                    output += " ";
                    st.pop();
                }
                if (!st.empty() && st.top() == '(')
                    st.pop();
                lastWasOperator = false;
            }
            else // 二元运算符
            {
                if (!output.empty() && output.back() != ' ')
                    output += " ";

                while (!st.empty() && pri(ch) <= pri(st.top()))
                {
                    output += st.top();
                    output += " ";
                    st.pop();
                }
                st.push(ch);
                lastWasOperator = true;
            }
        }
    }

    // 弹出栈中剩余运算符
    while (!st.empty())
    {
        if (!output.empty() && output.back() != ' ')
            output += " ";
        output += st.top();
        st.pop();
    }

    return output;
}

void Exe(const std::list<uint16_t>& l)
{
    std::cout << ">> Exe: " << L2S(l) << std::endl;
}

void Run(const std::list<uint16_t>& l)
{
    //std::cout<<"good-1";
    std::string pre = L2S(l);
    std::stack<double_t> num;
    double_t tmpn=0.00;
    double_t tmpo1=0.00, tmpo2=0.00;
    //num.push(0.00);
    //std::cout<<"good0";
    for(auto it = pre.begin(); it != pre.end(); ++it)
    {
        if(*it >= '0' && *it <= '9')
        {
            tmpn = tmpn*10.00 + *it - 48;
        }
        else if(*it == ' ')
        {
            num.push(tmpn);
            tmpn = 0.00;
        }
        else if (*it == '+' || *it == '-' || *it == '*' || *it == '/'|| *it == '^')
        {
        	if(num.empty())
           	{
				std::cout << "[Err 129] 用户正试图把栈挖穿." << std::endl;
				return;
			}
            tmpo2 = num.top();
            num.pop();
            //std::cout<<"good1";
            if(num.empty())
           	{
				std::cout << "[Err 129] 用户正试图把栈挖穿." << std::endl;
				return;
			}
            tmpo1 = num.top();
            num.pop();
            //std::cout<<"good2";
            if(*it == '+')
            {
                tmpn = (tmpo1+tmpo2);
            }
            else if(*it == '-')
            {
                tmpn = (tmpo1-tmpo2);
            }
            else if(*it == '*')
            {
                tmpn = (tmpo1*tmpo2);
            }
            else if(*it == '/')
            {
            	if(tmpo2 == 0.00)
            	{
					std::cout << "[Err 1] 用户正试图除以0来谋杀 Runtime." << std::endl;
					return;
				}
                tmpn = (tmpo1/tmpo2);
            }
            else if(*it == '^')
            {
            	if(tmpo1 == 0.00 && tmpo2 == 0.00)
            	{
            		std::cout << "[Err 4] 0^0? 唔..." << std::endl;
					return;
				}
                tmpn = pow(tmpo1,tmpo2);
            }
        }
    }
    if(tmpn != 2026.00)
    	std::cout << ">> Run: " << tmpn << std::endl;
    else
    	std::cout << "[Err 65] 栈溢出，Runtime 有1.4了." << std::endl;
}

int main()
{
	system("chcp 65001");
    pos = ex.begin();
    while(true)
    {
        s.resize(256);
        Oput(ex);
        printf("\n\nPos: %d\nAdd opt: ", *pos);
        std::cin >> s;


        uint32_t i;
        for(i=0; i<s.size(); i++)
        {
            if(!(s[i] >= '0' && s[i] <= '9' || s[i] == '+' || s[i] == '-' || s[i] == '*' || s[i] == '/' || s[i] == '^'|| s[i] == '(' || s[i] == ')'))
            {
                break;
            }
        }

        if(i == s.size())
        {
            for(i=0; i<s.size(); i++)
            {
                auto tmp = pos;
                ex.insert(++tmp, s[i]);
                ++pos;
            }
        }
        else if(s.size() == 1)
        {
            if(s == "l")
            {
                if(pos!=ex.begin())
                    --pos;
            }
            else if(s == "r")
            {
                if(pos!=--(--ex.end()))
                    ++pos;
            }
        }
        else if(s.size() == 3)
        {
            if(s == "del")
            {
                if(pos!=ex.begin())
                {
                    auto tmp = pos;
                    --pos;
                    ex.erase(tmp);
                }
            }
            else if(s == "exe")
            {
                Exe(ex);
            }
            else if(s == "run")
            {
                //std::cout<<"good-2";
                Run(ex);
            }
        }
        else if(s.size() == 6)
        {
            if(s == "delall")
            {
                ex.clear();
                ex.push_back(0x0000);
                ex.push_back(0x0001);
                pos = ex.begin();
            }
        }
		else
		{
			std::cout << "[Err 191] Interpreter 看不懂这家伙在些什么. 不过ta祝你新年快乐\\/" << std::endl;
		}
    }
}
