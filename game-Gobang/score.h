#ifndef SCORE_H
#define SCORE_H

#endif // SCORE_H
/* 棋型表示 */

/*分值定义

*/
//AI方
/*'11111'*/             const int WIN5 = 100000; // 可以成五
/*'_1111_'*/            const int ALIVE4 = 10000; // 活4
/*'__111__*2'*/         const int DOUBLEALIVE3 = 10000; // 两个以上的活3应该具有和活4一样的分值
/*'21111_'*/            const int DIE4 = 9000; // 死4
/*'21111_*2'*/          const int DOUBLEDIE4 = 10000; // 两个以上的死4应该具有单活4一样的分值
/*'21111__+__111__'*/   const int DIE4ALIVE3 = 10000; // 死4活3也是很高的分值
/*'2111_1_'*/
/*'211_11_'*/           const int LOWDIE4 =  1000; // 低级死4
/*'__111__'*/           const int ALIVE3 = 800; // 活3
/*'__11_1__'*/          const int JUMPLIVE3 = 700; // 跳活3
/*'__11__'*/            const int ALIVE2 = 200;  // 活2
/*'__11__*2'*/          const int DOUBLEALIVE2 = 400; // 双活2比单活2要高
/*'__1_1__'*/           const int LOWALIVE2 = 100; // 低级活2
/*'2111__'*/            const int DIE3 = 50; // 死3
/*'211__'*/             const int DIE2 = 20;  // 死2
/*'__1__'*/             const int ALIVE1 = 10; // 活1
/*'21__'*/              const int DIE1 = 1; // 死1
/*'__'*/                const int NOTHING = 0;


//AI敌方
/*'11111'*/             const int WIN5_2 = 100000; // 可以成五
/*'_1111_'*/            const int ALIVE4_2 = 100000; // 活4
/*'__111__*2'*/         const int DOUBLEALIVE3_2 = 100000; // 两个以上的活3应该具有和活4一样的分值
/*'21111_'*/            const int DIE4_2 = 30000; // 死4
/*'21111_*2'*/          const int DOUBLEDIE4_2 = 100000; // 两个以上的死4应该具有单活4一样的分值
/*'21111__+__111__'*/   const int DIE4ALIVE3_2 = 100000; // 死4活3也是很高的分值
/*'2111_1_'*/
/*'211_11_'*/           const int LOWDIE4_2 =  100000; // 低级死4
/*'__111__'*/           const int ALIVE3_2 = 100000; // 活3
/*'__11_1__'*/          const int JUMPLIVE3_2 = 7000; // 跳活3
/*'__11__'*/            const int ALIVE2_2 = 600;  // 活2
/*'__11__*2'*/          const int DOUBLEALIVE2_2 = 400; // 双活2比单活2要高
/*'__1_1__'*/           const int LOWALIVE2_2 = 100; // 低级活2
/*'2111__'*/            const int DIE3_2 = 50; // 死3
/*'211__'*/             const int DIE2_2 = 20;  // 死2
/*'__1__'*/             const int ALIVE1_2 = 10; // 活1
/*'21__'*/              const int DIE1_2 = 1; // 死1
/*'__'*/                const int NOTHING_2 = 0;

//具体棋形
