#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// -------> HELPER FUNCTIONS --------- //

// CUSTOM MODULO
int mod(int a, int b)
{
    return (a % b + b) % b;
}

// AFFINE CIPHER MAIN FUNCTION
char cipherChar(char ch, int a, int b, int m)
{
    if (isalpha(ch))
    {
        bool upper = isupper(ch);
        ch = tolower(ch);
        int x = ch - 'a';
        int res = mod((a * x + b), m);
        char c = res + 'a';
        return upper ? toupper(c) : c;
    }

    if (isdigit(ch))
    {
        int x = ch - '0';
        int res = mod((a * x + b), 10);
        return res + '0';
    }

    if (ispunct(ch) || ch == ' ')
        return ch;
    return ch;
}

// checking 'a' key satisifiable value
bool checkKey(int a, int m)
{
    int tmp_a = a;
    int tmp_m = m;
    while (tmp_m != 0)
    {
        int t = tmp_m;
        tmp_m = tmp_a % tmp_m;
        tmp_a = t;
    }
    return tmp_a == 1;
}

// -------> END OF HELPER FUNCTIONS --------- //

int main()
{
    string msg;
    int a, b;
    const int m = 26;

    cout << "enter the message: ";
    getline(cin, msg);

    cout << "enter key 'a' (must be coprime with 26): ";
    cin >> a;

    cout << "enter key 'b': ";
    cin >> b;

    while (!checkKey(a, m))
    {
        cout << "'a' must be coprime with 26. Try 1, 3, 5, 7, 11, 15, 17, 19, 21, 23, or 25" << endl;
        cout << "enter key 'a' (must be coprime with 26): ";
        cin >> a;
        // return 1;
    }

    string encrypted = "";
    for (char ch : msg)
    {
        encrypted += cipherChar(ch, a, b, m);
    }

    cout << "\noriginal message: " << msg << endl;
    cout << "encrypted message: " << encrypted << endl;

    return 0;
}