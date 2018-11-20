// реализация функций и классов для вычисления арифметических выражений
#include "arithmetic.h"
#include "stack.h"
string TPostfix::trimString(string source) {
	if (source.length() < 2) {
		return source;
	}
	if (source[0] == ' ') {
		source.erase(0, 1);
	}
	if (source[source.length() - 1] == ' ') {
		source.erase(source.length() - 1, 1);
	}
	for (int i = 0; i < source.length(); i++) {
		char c = source[i];
		if (c == ' ') {
			if (i < source.length() - 1) {
				char _c = source[i + 1];
				if (_c == '+' || _c == '/' || _c == '*') {
					source.erase(i, 1);
					i--;
				}
			}
		}
	}
	return source;
}
string TPostfix::convertString(string source) {
	for (size_t i = 0; i < source.length(); i++) {
		switch (source[i]) {
		case ' ':
			source.erase(i, 1);
			i--;
			continue;
		case '-':
			source.replace(i, 1, "+-");
			i++;
			continue;
		default:
			if ((int)source[i] >= (int)'a' && (int)source[i] <= (int)'z') {
				throw source[i];
			}
			break;
		}
	}
	return source;
}
double TPostfix::decodeVal(string value) {
	double div = 1;
	double result = 0;
	bool negative = false;
	const int sta = (int)('0');
	const int end = (int)('9');
	const int exc_1 = (int)('.');
	const int exc_2 = (int)('-');
	for (auto c : value) {
		int ch = (int)c;
		switch (ch) {
		case exc_1:
			div = 0.1;
			continue;
		case exc_2:
			negative = !negative;
			break;
		default:
			if (ch >= sta && ch <= end) {
				if (div > 0.5) {
					result *= 10;
				}
				result += (ch - sta)*div;
			}
		}
		if (div < 1) {
			div *= 0.1;
		}
	}
	if (negative) {
		result *= -1;
	}
	return result;
}
string TPostfix::getVal(string& source, size_t start) {
	string val;
	const int sta = (int)('0');
	const int end = (int)('9');
	const int exc_1 = (int)('.');
	const int exc_2 = (int)('-');
	const int exc_3 = (int)('x');
	for (int i = 0; start + i < source.length();) {
		int c = (int)source[start + i];
		switch (c) {
		case '+':
		case '*':
		case '/':
			if (val.length() == 0) {
				i++;
				continue;
			}
		default:
			if (c < sta || end < c) { return val; }
		case exc_1:
		case exc_2:
		case exc_3:
			val += source[start + i];
			source.erase(start + i, 1);
		}
	}
	return val;
}
void TPostfix::ToPostfixIteration(TStack<string>& _T, string source) {
	TStack<char> O(100);
	TStack<string> N(100);
	string result = "";
	char last = '\0';
	size_t lastPos;
	for (int i = 0; i < source.length(); i++) {
		char c = source[i];
		if (c == '(') {
			for (size_t j = i, off = 0; j < source.length(); j++) {
				char _c = source[j];
				if (_c == '(') {
					off++;
				}
				else if (_c == ')') {
					string h = source.substr(i + off, j - i - off);
					ToPostfixIteration(_T, h);
					source.replace(i + off - 1, j - i - off + 2, "x");
					i = -1;
				}
			}
		}
	}
	for (int i = 0; i < source.length(); i++) {
		char c = source[i];
		if (c == '/') {
			size_t sta;
			size_t end;
			for (sta = i; sta > 0; sta--) {
				if (source[sta] == '*' || source[sta] == '+') {
					sta++;
					break;
				}
			}
			for (end = i; end < source.length(); end++) {
				if (source[end] == '*' || source[end] == '+') {
					break;
				}
			}
			if (sta == 0 && end == source.length()) {
				break;
			}
			string h = source.substr(sta, end - sta);
			ToPostfixIteration(_T, h);
			source.replace(sta, end - sta, "x");
			i = -1;
		}
	}
	string base = source;
	while (base.length() > 0) {
		last = '\0';
		for (int i = 0; i < base.length(); i++) {
			switch (char c = base[i]) {
			case '+':
				if (last == '\0' || last == '*' || last == '/') {
					last = c;
					lastPos = i;
				}
				break;
			case '*':
			case '/':
				if (last == '\0') {
					last = c;
					lastPos = i;
				}
				break;
			default:
				base.erase(i, 1);
				i--;
			}
		}
		if (last != '\0') {
			O.Push(last);
			base.erase(lastPos, 1);
		}
	}
	string tempO = " ";
	for (int i = 0; i < source.length(); i++) {
		char c = source[i];
		if (c == '+' || c == '*' || c == '/') {
			if (c == O.GetTop()) {
				char tr = O.Pop();
				char td = tempO[tempO.length() - 1];
				if (td == ' ' || td == c && (td == '*' || td == '+')) {
					if (!N.IsEmpty()) {
						result += ' ' + N.Pop();
					}
					tempO += tr;
				}
				else {
					if (!N.IsEmpty()) {
						result += ' ' + N.Pop();
					}
					result += tempO;
					tempO = tr;
				}
				source.erase(i, 1);
				i--;// = -1;
			}
			else {
				if (!N.IsEmpty()) {
					result += ' ' + N.Pop();
				}
			}
		}
		else {
			N.Push(getVal(source, i));
			i = -1;
		}
	}
	if (!N.IsEmpty()) {
		result += ' ' + N.Pop();
	}
	result += tempO;
	_T.Push(result);
}
string TPostfix::ToPostfix(string source) {
	if (source == "\0") {
		source = infix;
	}
	else {
		source = convertString(source);
	}
	if (source.length() < 1) {
		return source;
	}
	ToPostfixIteration(_T, source);
	string temp = _T.Pop();
	while (!(_T.IsEmpty())) {
		for (int i = temp.length(); i >= 0; --i) {
			if (temp[i] == ' ') {
				if (i + 1 == temp.length()) {
					temp.erase(i, 1);
				}
				else {
					if (temp[i + 1] == ' ' || temp[i + 1] == '+' || temp[i + 1] == '/' || temp[i + 1] == '*') {
						temp.erase(i, 1);
					}
				}
			}
			if (temp[i] == 'x') {
				temp.erase(i, 1);
				string h = _T.Pop();
				temp.insert(i, h);
				i = temp.length() - 1;
			}
		}
	}
	temp = trimString(temp);
	return temp;
}
double TPostfix::Calculate(string source) { // Ввод переменных, вычисление по постфиксной форме
	TStack<double> _D(100);
	if (source == "\0") {
		source = postfix;
	}
	for (int i = 0; i < source.length(); i++) {
		switch (source[i]) {
		default: {
			_D.Push(decodeVal(getVal(source, i)));
			i = -1;
			continue;
		}
		case ' ': {
			break;
		}
		case '+': {
			_D.Push(_D.Pop() + _D.Pop());
			break;
		}
		case '*': {
			_D.Push(_D.Pop() * _D.Pop());
			break;
		}
		case '/': {
			double temp = _D.Pop();
			if (temp == 0) {
				throw temp;
			}
			_D.Push(_D.Pop() / temp);
			break;
		}
		}
		source.erase(0, 1);
		i = -1;
	}
	return _D.Pop();
}
void TPostfix::SetInfix(string base) {
	infix = convertString(base);
	postfix = ToPostfix();
	while (!_T.IsEmpty()) {
		_T.Pop();
	}
}