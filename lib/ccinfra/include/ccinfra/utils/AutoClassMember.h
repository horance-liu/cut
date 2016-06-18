#ifndef CCINFRA_AUTOCLASSMEMBER_H_
#define CCINFRA_AUTOCLASSMEMBER_H_


#define AUTO_CLASS_MEMBER_1(class_name, t1, n1) \
		                    class_name( t1  n1) \
		                    : n1(n1) {} \
		                    private: \
		                      t1 n1

#define __AUTO_CLASS_MEMBER_2(class_name, t1, n1, t2, n2) \
                            private: \
                              t1 n1; t2 n2;             \
                            public:                     \
                            class_name( t1  n1, t2  n2) \
                            : n1(n1), n2(n2)

#define AUTO_CLASS_MEMBER_2(class_name, t1, n1, t2, n2) \
		                    class_name( t1  n1, t2  n2) \
		                    : n1(n1), n2(n2) {} \
		                    private: \
		                      t1 n1; t2 n2

#define __AUTO_CLASS_MEMBER_3(class_name, t1, n1, t2, n2, t3, n3) \
                            private: \
                              t1 n1; t2 n2; t3 n3; \
                            public: \
                            class_name( t1  n1, t2  n2, t3  n3) \
                            : n1(n1), n2(n2), n3(n3)

#define AUTO_CLASS_MEMBER_3(class_name, t1, n1, t2, n2, t3, n3) \
		                    class_name( t1  n1, t2  n2, t3  n3) \
		                    : n1(n1), n2(n2), n3(n3) {} \
		                    private: \
		                      t1 n1; t2 n2; t3 n3

#define AUTO_CLASS_MEMBER_4(class_name, t1, n1, t2, n2, t3, n3, t4, n4) \
		                    class_name( t1  n1, t2  n2, t3  n3, t4  n4) \
		                    : n1(n1), n2(n2), n3(n3), n4(n4) {} \
		                    private: \
		                      t1 n1; t2 n2; t3 n3; t4 n4

#define AUTO_CLASS_MEMBER_5(class_name, t1, n1, t2, n2, t3, n3, t4, n4, t5, n5) \
		                    class_name( t1  n1, t2  n2, t3  n3, t4  n4, t5  n5) \
		                    : n1(n1), n2(n2), n3(n3), n4(n4), n5(n5) {} \
		                    private: \
		                      t1 n1; t2 n2; t3 n3; t4 n4; t5 n5

#define AUTO_CLASS_MEMBER_6(class_name, t1, n1, t2, n2, t3, n3, t4, n4, t5, n5, t6, n6) \
		                    class_name( t1  n1, t2  n2, t3  n3, t4  n4, t5  n5, t6  n6) \
		                    : n1(n1), n2(n2), n3(n3), n4(n4), n5(n5), n6(n6) {} \
		                    private: \
		                      t1 n1; t2 n2; t3 n3; t4 n4; t5 n5; t6 n6


#endif
