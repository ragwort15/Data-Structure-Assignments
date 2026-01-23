#include "space.h"

int countHits(std::vector<Asteroid> a) {
    std::stack<Asteroid> asteroidStack;

    for (Asteroid& asteroid: a) {
        if (asteroid.d == Direction::right) { // O(1)..n times = O(n)
            asteroidStack.push(asteroid);
        } else {
            while (!asteroidStack.empty()) {
                auto lastAsteroid = asteroidStack.top();

                if (lastAsteroid.m == asteroid.m) {
                    // Both vaporizes
                    asteroidStack.pop();
                    break;
                } else if (lastAsteroid.m < asteroid.m) {
                    // Last right going asteroid vaporizes
                    asteroidStack.pop();
                } else {
                    // Left going asteroid vaporizes
                    break;
                }
            }
        }
    }

    return asteroidStack.size();
}
void test1() {
    // (A1:m=10,d=right); (A2:m=11,d=left);(A3:m=11,d=right);(A4:m=5,d=left)
    Asteroid A1(10, Direction::right);
    Asteroid A2(11, Direction::left);
    Asteroid A3(11, Direction::right);
    Asteroid A4(5, Direction::left);

    std::vector<Asteroid> asteroids;
    asteroids.push_back(A1);
    asteroids.push_back(A2);
    asteroids.push_back(A3);
    asteroids.push_back(A4);

    std::cout << "test1() -> Number of hits: " << countHits(asteroids) << std::endl;
}

void test2() {
    // (A1:m=10,d=right); (A2:m=11,d=right);(A3:m=11,d=right)
    Asteroid A1(10, Direction::right);
    Asteroid A2(11, Direction::right);
    Asteroid A3(11, Direction::right);

    std::vector<Asteroid> asteroids;
    asteroids.push_back(A1);
    asteroids.push_back(A2);
    asteroids.push_back(A3);

    std::cout << "test2() -> Number of hits: " << countHits(asteroids) << std::endl;
}

void test3() {
    // std::vector<Asteroid> test3 = {
    //      {1, right}, {1, left}, {1, right}, {1, left}
    // };
    Asteroid A1(1, Direction::right);
    Asteroid A2(1, Direction::left);
    Asteroid A3(1, Direction::right);
    Asteroid A4(1, Direction::left);

    std::vector<Asteroid> asteroids;
    asteroids.push_back(A1);
    asteroids.push_back(A2);
    asteroids.push_back(A3);
    asteroids.push_back(A4);

    std::cout << "test3() -> Number of hits: " << countHits(asteroids) << std::endl;
}

void test4() {
    // std::vector<Asteroid> test4 = {
    //      {5, right}, {1, right}, {3, right}, {8, left}
    // };
    Asteroid A1(5, Direction::right);
    Asteroid A2(1, Direction::left);
    Asteroid A3(3, Direction::right);
    Asteroid A4(8, Direction::left);

    std::vector<Asteroid> asteroids;
    asteroids.push_back(A1);
    asteroids.push_back(A2);
    asteroids.push_back(A3);
    asteroids.push_back(A4);

    std::cout << "test4() -> Number of hits: " << countHits(asteroids) << std::endl;
}

//Time Complexity: O(n)---each asteroid is pushed and popped at most once

//Space Complexity: O(n)---the size on the stack
//n = number of asteroids in the vector
 