## 개요
Dining Philosophers 문제를 각각 Resource all resource(No Hold and Wait), Resource ordering, Bankers algorithm으로 해결하였다.

[깃허브 바로가기](https://github.com/logicallaw/INHA_OperatingSystem_003/tree/main/src/dining_philosophers_problems)

## 문제해결 방법
**1.Requesting all resources(No Hold and Wait)**
한 철학자는 자원에 대한 요청을 할 때 모든 자원을 요청하도록 세마포어 변수 once를 통해 왼쪽 포크와 오른쪽 포크를 동시에 잡도록 구현하였다. 이는 교착상태가 발생하는 4가지 조건 중 점유대기 조건을 예방하도록 함으로써 교착상태를 피할 수 있는 방법이다.

**2.Resource ordering**
현재 5명의 철학자 중 마지막 철학자에 대해서 자원요청 순서에 대한 일관성을 유지하기 위하여 else 분기문을 통해 적절하게 처리하도록 구현하였다. 기존 코드의 마지막 철학자는 4번 포크 요청 후 0번 포크를 요청하지만, 오름차순의 자원 요청 순서에 따른 0번 포크 요청 후 4번 포크를 요청하도록 구현하였다. 이는 교착상태가 발생하는 4가지 조건 중 순환대기 조건을 예방함으로써 교착상태를 피할 수 있는 방법이다.

**3.Bankers algorithm**
사전에 알고 있는 claim 정보를 바탕으로 동적으로 철학자가 자원을 요청하였을 때, allocation시 문제 발생할지 여부를 safe state 기준으로 판단하여 safe한 요청이면 자원을 allocation하고, 그렇지 않으면 blocked 시키는 방법으로 교착상태를 회피하는 알고리즘을 구현하였다.

먼저, 2차원 행렬인 C, A는 각각 claim metrix, allocation metrix(28, 30번째줄)를 의미하며 claim metrix 초기화는 사전에 각 철학자는 왼쪽 포크와 오른쪽 포크를 최대로 1개씩 요청할 수 있어서 tables_init(48번째줄) 함수와 같이 초기화하였고, allocation metrix는 초기에는 할당된 포크가 없으므로 0(48번째줄)으로 초기화를 진행하였다.

bankers_request 함수(62번째줄)를 보면, 매번 동적으로 각 철학자마다 Worst-case에 추가로 요청 가능한 가용 자원의 수를 계산하면서 Need가 Available보다 작다면(request[j] <= V[j], 81번째줄) safe로 판단하여 자원을 할당시키고, 그렇지 않다면 pthread_cond_wait(&bankers_cond, &bankers_mutex);로 그 철학자를 go to sleep(blocked) 시킨다. safe한 상황에서는 절대로 교착상태가 발생하지 않음을 보장하므로 현재 가용 가능한 자원을 그 철학자에게 allocation(A[philosopher_num][j] += request[j], 90번째줄) 한다.

bankers_release 함수(95번째줄)를 보면, 해당 철학자는 현재 할당된 모든 자원을 반납해야되므로 V[j] += A[philosopher_num][j];, A[philosoper_num][j] = 0;과 같이 동작하도록 구현하였다. 이후, 현재 blocked된 모든 철학자 쓰레드를 동시에 awake(Ready state로 전이)함으로써 다음 철학자에게 allocation 할 수 있도록 구현하였다. 이러한 과정은 Allocation sequence를 생성하므로 절대로 교착상태가 발생하지 않을 것이다.

## 구현결과(스냅샷)
**1.개발환경**
운영체제: macOS Sequoia 15.5
프로세서: Apple M1
편집도구: Visual Studio Code v1.101.0
빌드도구: cmake v3.31.6
C++ 컴파일러: Apple clang v16.0.0

**2.빌드 방법**
1. Create a build directory:
   ```bash
   mkdir build && cd build
   ```

2. Compile your source code:
   ```bash
   cmake ..
   ```

3. Run make:
   ```bash
   make
   ```

4. Run the executable (e.g. Resource ordering):
    ```bash
    ./Resource ordering
    ```

5. Etc./ shortcut command:
   ```
   cmake .. && make && ./Resource ordering
   ```

**3.실행 결과(일부분)**
- Requesting all resources
![Requesting all resources](./no_hold_and_wait_snapshot.png)

- Resource ordering
![Resource ordering](./resource_ordering_snapshot.png)

- Bankers algorithm
![Bankers algorithm](./bankers_algorithm_snapshot.png)

## 평가
**1.Requesting all resources**
- 세마포어 변수 once에 대한 main에서의 적절한 초기화가 이루어졌다. 초깃값은 1로써 해당 임계영역은 한 명의 철학자만 들어갈 수 있도록 상호배제 하였다.
- 임계자원에 해당하는 왼쪽포크(philosopher_num)과 오른쪽포크(philosopher_num + 1)에 대한 한 명의 철학자가 요청 시점에 모든 자원을 요청하도록 세마포어 once를 사용한 guard가 적절한 위치에서 이루어지고 있다.

**2.Resource ordering**
- 자원 요청 순서를 오름차순으로 일관되게 요청하도록 제약을 줌으로써 순환대기를 적절하게 방지하여 교착상태를 예방하였다.
- 하지만, 현재 알고리즘은 5명의 철학자에 한정된 것으로, 확장성에 있어서 유지보수에 어려움이 있을 것으로 예상된다.
- 그럼에도 5명의 철학자 조건하에는 교착상태가 발생하지 않음을 보장하기에 효과적인 해결책으로 평가된다.

**3.Bankers algorithm**
- 사전에 알고 있는 claim edge 정보를 기반으로 교착상태 회피를 Bankers algorithm을 기반으로 적절하게 구현하였다.
- tables_init, bankers_request, bankers_release와 같이 적절하게 기능 단위로 모듈화가 이루어졌다.
- enum 상수인 safety_t를 도입하여 가독성 및 유지보수성을 높였다.
- 공유자원인 C, A, V에 대한 상호배제가 적절히 이루어졌다.

## 결론 및 느낀점
**1.결론**
Requesting all resource(No Hold and Wait), Resource ordering, 그리고 Bankers algorithm을 통해 식사하는 철학자 문제의 교착상태를 예방 및 회피를 구현하였다. 특히, Bankers algorithm은 동적으로 안전성을 검사를 통해 자원의 효율성을 유지함을 확인할 수 있다. 또한, 적절한 기능별로 코드를 분리하여 코드 가독성 및 유지보수성을 향상시켰다.

**2.느낀점**
평소에 프로그래밍을 하면서 경험하기 어려운 교착상태 문제를 세 가지 전략을 통해 해결함으로써 이론적인 개념을 깊이 이해할 수 있었습니다.