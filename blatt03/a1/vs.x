/* Sourcecode by David Schwarzmann, 29.05.17 */
struct add_params {
	long p1;
	long p2;
};

struct concat_params {
	string str1<>;
	string str2<>;
};

struct split_return {
	string pre<>;
	string post<>;
};

program VS11SERVER {
	version VSSERVERVERS {
		long vs_square(long)=1;
		long vs_add(add_params)=2;
		string vs_concat(concat_params)=3;
		split_return vs_split(string)=4;
		void vs_increment(long)=5;
		void vs_Shutdown(void)=6;
	}=1;
} = 0x20004123;
