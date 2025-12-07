#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Transition {
	string nxtState;
	string push;
	int rule;
	string grammar;
};

bool isEmpty(char c) { return c == '#'; }

string stackAsString(stack<char> st) {
	string s;
	while (!st.empty()) {
		char c = st.top();
		st.pop();
		s += c;
	}
	reverse(s.begin(), s.end());
	return s.empty() ? "e" : s;
}

int main() {
	string userInput;
	cout << "Please enter input: ";
	cin >> userInput;

	userInput.push_back('$');
	string state = "p";
	stack<char> st;
	int step = 0;
	int ip = 0;

	cout << left << setw(6) << "Step" << setw(8) << "State" << setw(15) << "Unread" << setw(10) << "Stack" << setw(12) << "Δ Used" << "R Used" << "\n";

	auto rowPrint = [&](int step, string stt, string unread, stack<char> stk, string d, string r) {
		cout << left << setw(6) << step << setw(8) << stt << setw(15) << unread << setw(10) << stackAsString(stk) << setw(12) << d << r << "\n";
	};

	rowPrint(step++, state, userInput, st, "--", "");

	while (true) {
		char a = userInput[ip];
		char X = st.empty() ? 'e' : st.top();

		if (state == "p" && st.empty()) {
			state = "q";
			st.push('S');
			rowPrint(step++, state, userInput.substr(ip), st, "1", "");
			continue;
		}

		if (state == "q" && a == 'a') {
			state = "qa";
			rowPrint(step++, state, userInput.substr(ip), st, "2", "");
			continue;
		}

		 if (state == "qa" && X == 'S' && a == 'a') {
                        st.pop();
                        st.push('b');
                        st.push('S');
                        st.push('a');
                        rowPrint(step++, state, userInput.substr(ip), st, "7", "S -> aSb");
                        continue;
                }
	
		if ((state == "q" || state == "qa") && X == 'a' && a == 'a') {
                        st.pop();
                        ip++;
                        rowPrint(step++, state, userInput.substr(ip), st, "3", "");
			if(state=="qa") state="q";
                        continue;
                }

		if (state == "q" && a == 'b') {
			state = "qb";
			rowPrint(step++, state, userInput.substr(ip), st, "4", "");
			continue;
		}

 		if (X == 'S' && (a == 'b' || a == '$')) {
                        st.pop();
                        rowPrint(step++, state, userInput.substr(ip), st, "8", "S -> e");
                        continue;
                }

		if ((state == "q" || state == "qb") && X == 'b' && a == 'b') {
			st.pop();
			ip++;
			if(state == "qb") state = "q";
			rowPrint(step++, state, userInput.substr(ip), st, "5", "");
			continue;
		}

		if (state == "q" && a == '$' && st.empty()) {
			state = "q$";
			rowPrint(step++, state, userInput.substr(ip), st, "6", "");
			break;
		}

		cerr << "Error: No valid transition\n";
		return 1;
	}

	cout << "Input accepted\n";
	return 0;
}
	


