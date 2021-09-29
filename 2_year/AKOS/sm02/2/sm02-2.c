// 2 задача/ 2дз с семинара 199
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

int32_t satsum(int32_t v1, int32_t v2){
    int32_t c;
    if(!__builtin_add_overflow(v1, v2, &c)){
        return c;
    }
    //v1 < 0, v2<0 
    // в других случаях переполнения нит
    if ( v1 < 0){
        return (int32_t)(1u << 31);
    }
    // v1 > 0, v2 > 0
    return (int32_t) ((1u << 31) - 1u);
}
// INT_MAX // 1u << 31 - 1 // 100000...000 -> 01111...111
// INT_MIN // (int32_t) (1u << 31) 
// int main(){
//     int32_t a, b;
//     scanf("%" SCNd32 "%" SCNd32 "", &a, &b);
//     printf("%" SCNd32 "", satsum(a, b));
// }