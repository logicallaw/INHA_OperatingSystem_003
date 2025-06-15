## 개요
Dining Philosophers 문제를 각각 Resource all resource(No Hold and Wait), Resource ordering, Bankers algorithm으로 해결하였다.

[깃허브 바로가기](https://github.com/logicallaw/INHA_OperatingSystem_003/tree/main/src/dining_philosophers_problems)

## 문제해결 방법
**1.Requesting all resources(No Hold and Wait)**
한 철학자는 자원에 대한 요청을 할 때 모든 자원을 요청하도록 세마포어 변수 once를 통해 왼쪽 포크와 오른쪽 포크를 동시에 잡도록 구현하였다. 이는 교착상태가 발생하는 4가지 조건 중 점유대기 조건을 예방하도록 함으로써 교착상태를 피할 수 있는 방법이다.

**2.Resource ordering**
현재 5명의 철학자 중 마지막 철학자에 대해서 자원요청 순서에 대한 일관성을 유지하기 위하여 else 분기문을 통해 적절하게 처리하도록 구현하였다. 기존 코드의 마지막 철학자는 4번 포크 요청 후 0번 포크를 요청하지만, 오름차순의 자원 요청 순서에 따른 0번 포크 요청 후 4번 포크를 요청하도록 구현하였다. 이는 교착상태가 발생하는 4가지 조건 중 순환대기 조건을 예방함으로써 교착상태를 피할 수 있는 방법이다.

**3.Bankers algorithm**

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

## 결론 및 느낀점
**1.결론**

**2.느낀점**

