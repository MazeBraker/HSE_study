//partial 2tests
#include <stdio.h>
int main(){
	signed long long x;
	// char *reject = "reject";
	char *summon = "summon";
	char *disqualify = "disqualify";
	while (scanf("%lld", &x) != EOF){
		printf("%s\n", x > 5?summon:disqualify);
		//
	}
	return 0;
}