#include<bits/stdc++.h>
using namespace std;

class Bignum{
	public:

	string num = "";

	Bignum(){
		this->num = "0";
	}

	Bignum(long long x){
		while(x){
			this->num += (x % 10 + '0');
			x /= 10;			
		}
		reverse(this->num.begin(),this->num.end());
	}

	Bignum(string s){
		this->num = s;
	}

	int length(){
		return this->num.size();	
	}

	string get(){
		return this->num;
	}

	void add(Bignum x){
		string s1 = this->get();
		string s2 = x.get();
		reverse(s1.begin(),s1.end());
		reverse(s2.begin(),s2.end());
		vector<int> digits;
		for(int i = 0; i < max(x.length(),this->length()); i++){
			int tmp1 = 0, tmp2 = 0;
			if(i < x.length()) tmp1 = s2[i] - '0';
			if(i < this->length()) tmp2 = s1[i] - '0';
			digits.push_back(tmp1+tmp2);
		}
		string result = "";
		for(int i = 0; i < digits.size(); i++){
			if(i + 1 == digits.size()){
				if(digits[i] >= 10){
					result += (digits[i]%10 + '0');
					result += (digits[i]/10 + '0');
				} else {
					result += (digits[i] + '0');
				}
			} else {
				result += (digits[i] % 10 + '0');
				digits[i+1] += digits[i] / 10;
			}
		}
		while(result.back() == '0') result.pop_back();
		reverse(result.begin(),result.end());
		this->num = result;
	}

	void subtract(Bignum x){
		string s1 = this->get();
		string s2 = x.get();
		reverse(s1.begin(),s1.end());
		reverse(s2.begin(),s2.end());
		vector<int> digits;
		for(int i = 0; i < max(x.length(),this->length()); i++){
			int tmp1 = 0, tmp2 = 0;
			if(i < x.length()) tmp1 = s2[i] - '0';
			if(i < this->length()) tmp2 = s1[i] - '0';
			digits.push_back(tmp2-tmp1);
		}
		string result = "";
		for(int i = 0; i < digits.size(); i++){
			if(i == digits.size() - 1 && digits[i] < 0) assert(false);
			if(digits[i] < 0){
				digits[i] += 10;
				digits[i+1]--;
			}
			result += (digits[i] + '0');
		}
		while(result.back() == '0') result.pop_back();
		reverse(result.begin(),result.end());
		this->num = result;
	}

	void multiply(Bignum x){
		string s1 = this->get();
		string s2 = x.get();
		reverse(s1.begin(),s1.end());
		reverse(s2.begin(),s2.end());
		vector<int> digits(this->length() + x.length());
		for(int i = 0; i < x.length(); i++){
			for(int j = 0; j < this->length(); j++){
				digits[i+j] += ((s2[i] - '0') * (s1[j] - '0'));
			}
		}
		string result = "";
		for(int i = 0; i < digits.size(); i++){
			if(i == digits.size() - 1 && digits[i] >= 10) assert(false);
			result += (digits[i] % 10 + '0');
			if(i != digits.size() - 1) digits[i+1] += digits[i]/10;
		}
		while(result.back() == '0') result.pop_back();
		reverse(result.begin(),result.end());
		this->num = result;
	}

	bool isGreater(Bignum x){
		if(x.length() > this->length()) return true;
		else if(x.length() < this->length()) return false;
		string s1 = this->get();
		string s2 = x.get();
		for(int i = 0; i < x.length(); i++){
			if(s1[i] == s2[i]) continue;
			if(s2[i] > s1[i]) return true;
			else return false;
		} 
		return false;
	}

	void operator+=(Bignum x){
		this->add(x);
	}

	void operator-=(Bignum x){
		this->subtract(x);
	}

	void operator*=(Bignum x){
		this->multiply(x);
	}

	bool operator<(Bignum x){
		return isGreater(x);
	}
		
	bool operator==(Bignum x){
		return (this->get() == x.get());
	}

	bool operator>(Bignum x){
		return !((*this) == x || (*this) < x); 
	}

	bool operator>=(Bignum x){
		return !((*this) < x); 
	}

	bool operator<=(Bignum x){
		return !((*this) > x);
	}

};

int main(){
}
