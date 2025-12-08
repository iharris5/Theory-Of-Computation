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
		s = st.top() + s;
		st.pop();
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

	auto getUnread = [&](int ipSnapshot) -> string {
        	if (ipSnapshot >= userInput.size()) return "e"; 
        	string unread = userInput.substr(ipSnapshot);
		return (unread == "$") ? "e" : unread;
    	};

	auto rowPrint = [&](int step, string stt, stack<char> stk, string d, string r, int ipSnapshot) {
		cout << left << setw(6) << step << setw(8) << stt << setw(15) << getUnread(ipSnapshot) << setw(10) << stackAsString(stk) << setw(12) << d << r << "\n";
	};

	cout << left << setw(6) << "Step" << setw(8) << "State" << setw(15)
         << "Unread Input" << setw(10) << "Stack" << setw(12) << "Δ Used" << "R Used" << "\n";

	rowPrint(step++, state, st, "--", "", ip);

	while (true) {
		char a = userInput[ip];
		char X = st.empty() ? 'e' : st.top();

		if (state == "p" && st.empty()) {
			state = "q";
			st.push('S');
			rowPrint(step++, state, st, "1", "", ip);
			continue;
		}

		if (state == "q" && a == 'a') {
			state = "qa";
			rowPrint(step++, state, st, "2", "", ip);
			continue;
		}

		 if (state == "qa" && X == 'S' && a == 'a') {
                        st.pop();
                        st.push('b');
                        st.push('S');
                        st.push('a');
                        rowPrint(step++, state, st, "7", "S -> aSb", ip);
                        continue;
                }
	
		if ((state == "q" || state == "qa") && X == 'a' && a == 'a') {
                        st.pop();
                        ip++;
			if (state == "qa") state = "q";
                        rowPrint(step++, state, st, "3", "", ip);
                        continue;
                }

		if (state == "q" && a == 'b') {
			state = "qb";
			rowPrint(step++, state, st, "4", "", ip);
			continue;
		}

 		if (X == 'S' && (a == 'b' || a == '$')) {
                        st.pop();
                        rowPrint(step++, state, st, "8", "S -> e", ip);
                        continue;
                }

		if ((state == "q" || state == "qb") && X == 'b' && a == 'b') {
			st.pop();
			ip++;
			if(state == "qb") state = "q";
			rowPrint(step++, state, st, "5", "", ip);
			continue;
		}

		if (state == "q" && a == '$' && st.empty()) {
			state = "q$";
			rowPrint(step++, state, st, "6", "", ip);
			break;
		}

		cerr << "Error: No valid transition\n";
		return 1;
	}

	cout << "Input accepted\n";
	return 0;
}
	


