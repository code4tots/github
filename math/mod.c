/*
3.4.2012

Some modular arithmetic stuff.
*/
#include<stdio.h>


// Left Hand Side
int LHS(int m, int mod){ int i, j;
	//m^6 - 3m^3 + 3
	int m3 = 1;
	int m6;
	int ret;
	// calculate m3
	for (i = 0; i < 3; i++){
		m3 = (m3 * m) % mod;
	}
	// calculate m6
	m6 = m3;
	for (i = 0; i < 3; i++){
		m6 = (m6 * m) % mod;
	}
	// Calculate m6 - 3m3 + 3, i.e. m6 + 3( -m3 ) + 3
	ret = (m6 + 3 * (mod - m3) + 3 ) % mod;
	return ret;
}

// Right Hand Side
int RHS(int p, int mod){ int i, j;
	//p^3
	p %= mod;
	return ( ((p*p)%mod)*p )%mod;
}



int main(int argc, char* argv[]){ int i, j;
	int mod, x, y, L, R;
	for (mod = 2; mod < 100; mod++){
		// I want to find mod such that 
		// it is impossible for LHS(x,mod) == RHS(y,mod)
		// no matter what values I plug into x or y.
		
		for (x = 0; x < mod; x++){
			L = LHS(x, mod);
			for (y = 0; y < mod; y++){
				R = RHS(y,mod);
				if (L == R){
					printf("failed: mod=%d, x=%d=>%d, y=%d=>%d\n", mod, x, L, y, R);
					goto failed;
				}
			}
		}
		
		// if we are here, success!!
		printf("mod: %d\n", mod);
		
	// break out of nested loop if L == RHS(y,mod)
	failed:
		L = 0;
	}
	return 0;
}
