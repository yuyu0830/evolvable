#include <iostream>
#include <vector>
#include <math.h>
#include <cstring>
#include <algorithm>
#define MAX 999999999
#define NUM 100001
#define fastio ios_base::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);

using namespace std;

typedef struct node {
	int value = 0;
	node* next = nullptr;
	node(int V) : value(V) {};
};

int n;
string s;
bool valid = true;

int convert(char c) {
	if (c < 48) return c - 30;
	return c - 48;
}

int typeof(int v) {
	if (v < 10) return 0; // 숫자
	else if (v > 11) return 1; // 연산자
	return 2; // 괄호
}

node* GetEnd(node* ptr) {
	if (!ptr) return ptr;
	node* tmp = ptr;
	while (tmp->next != nullptr) {
		tmp = tmp->next;
	}
	return tmp;
}

int f(int start) {
	int pos = start;
	int tmpNum = 0;
	bool fValid[3] = {true, false, true};
	node* num = nullptr;
	node* sign = nullptr;

	while (pos < s.size() && s[pos] != ')') {
		int v = convert(s[pos]);
		int type = typeof(v);

		// 나올 차례가 아닌게 나오면 바로 고냥 리턴
		if (!fValid[type]) {
			valid = false;
			return 0;
		}

		switch (type) {
		case 0: // 숫자면
			tmpNum = tmpNum * 10 + v;
			fValid[1] = true;
			fValid[2] = false;
			break;

		case 1: // 연산자면
			// 숫자 노드 생성
			if (!num) num = new node(tmpNum);
			else {
				node* nTmp = GetEnd(num);
				nTmp->next = new node(tmpNum);
			}
			tmpNum = 0;

			// 연산자 노드 생성
			if (!sign) sign = new node(v);
			else {
				node* sTmp = GetEnd(sign);
				sTmp->next = new node(v);
			}
			break;

		default: // 괄호면
			tmpNum = f(pos + 1);
			fValid[0] = false;
			fValid[1] = true;
			fValid[2] = false;
			break;
		}

		pos++;
	}

	node* tmp = num;
	while (tmp) {
		printf("num : %d\n", tmp->value);
		tmp = tmp->next;
	}
}

int main() {
	fastio;
	cin >> s;
	f(0);
	printf("%d\n", valid);
}
