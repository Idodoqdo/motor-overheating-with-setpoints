#include <iostream>
#include <array>
#include <cmath>
#include "matrix.h"


class iEngine {
 public:
    void virtual heating_rate_calculation() = 0;
    void virtual cooling_rate_calculation() = 0;
    void virtual a_calculation() = 0;
    void virtual M_col_calculation() = 0;
    void virtual V_col_calculation() = 0;
    void virtual heat() = 0;
    int virtual  get_t() = 0;
    void virtual the_total_effect_of_speeds() = 0;
};


class Engine : public iEngine {
 protected:
    double I;
    int M_num;
    int V_num;
    int t;
    double a;
    double T_end;
    double H_m;
    double H_v;
    double C;
    double T_engine;
    double V_h;
    double V_c;
    double V_col;
    double M_col;
    std::array<int, 6> M; // можно изменить на vector, елси мы точно знаем, что будет меняться количество
    std::array<int, 6> V; // зависиммых переменных
    void heating_rate_calculation() override;
    void cooling_rate_calculation() override;
    void a_calculation() override;
    void M_col_calculation() override;
    void V_col_calculation() override;
    void heat() override;
    void the_total_effect_of_speeds() override;
    void new_segment();
 public:
    double T_environment;
    explicit Engine (double Start_T) : T_engine(Start_T) ,T_environment(Start_T)  {
        M = {20, 75, 100, 105, 75, 0};
        V = {0, 75, 150, 200, 250, 300};
        I = 10;
        T_end = 110;
        H_m = 0.01;
        H_v = 0.0001;
        C = 0.1;
        t = 0;
        M_num = 0;
        V_num = 0;
        V_col = 0;
        M_col = 0;
    };
    int get_t() override {
        heat();
        return t;}
 private:
    std::pair<double, double> find_coef();
};

void Engine::heating_rate_calculation() {
    V_h = M_col * H_m + pow(V_col, 2) * H_v;
}

void Engine::cooling_rate_calculation() {
    V_c = C * (T_environment - T_engine);
}

void Engine::a_calculation() {
    a = M_col / I;
}

void Engine::new_segment() {
    V_num++;
    M_num++;  
}

typename std::pair<double,double> Engine::find_coef () {
    std::pair<double, double> rez;
    Matrix A(2, 2), B(2, 1), C(2, 1);
    A(0, 0) = V[V_num];
    A(0, 1) = 1;
    A(1, 0) = V[V_num + 1];
    A(1, 1) = 1;
    B(0, 0) = M[M_num];
    B(1, 0) = M[M_num + 1];
    C = A.inverse_matrix() * B;
    rez.first = C(0, 0);
    rez.second = C(1, 0);
    return rez;
}

void Engine::M_col_calculation() {
    std::pair<double,double> coef = find_coef();
    M_col = coef.first * V_col + coef.second;
}

void Engine::V_col_calculation() {
    V_col += a;
}

void Engine::the_total_effect_of_speeds() {
    double Tsum = V_h + V_c;
    T_engine += Tsum;
}

void Engine::heat() {
    while (T_engine <= T_end) {
        if (V_num < (int)V.size() - 1 && V[V_num + 1] <= V_col) {
            new_segment();
        }
        M_col_calculation();
        a_calculation();  
        V_col_calculation();
        heating_rate_calculation();
        cooling_rate_calculation();
        the_total_effect_of_speeds();
        ++t;
    }
}



