typedef string arrT[10];
arrT &func(void);


auto func(void)->string (&) [10];


string arrS[10];
decltype(arrS) &func(void);
