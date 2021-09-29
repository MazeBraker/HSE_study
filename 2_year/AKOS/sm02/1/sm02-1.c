#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint32_t satsum(uint32_t v1, uint32_t v2){
  uint32_t c = v1 + v2;
  if (c < v1)  
    c = ~(uint32_t)(0);
  return c;
}
// int main(){
//   uint32_t a, b;
//   scanf("%u %u", &a, &b);
//   printf("%u", satsum(a, b));
//   return 0;
// }