#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
double P_D(const string& d) {
    if (d == "Easy") return 0.6;
    if (d == "Hard") return 0.4;
    return 0.0;
}
double P_I(const string& i) {
    if (i == "High") return 0.7;
    if (i == "Low")  return 0.3;
    return 0.0;
}
double P_G_given_DI(const string& g, const string& d, const string& i) {
    double pGood;
    if      (d=="Easy" && i=="High") pGood = 0.9;
    else if (d=="Easy" && i=="Low")  pGood = 0.6;
    else if (d=="Hard" && i=="High") pGood = 0.7;
    else if (d=="Hard" && i=="Low")  pGood = 0.2;
    else return 0.0;
    return (g == "Good") ? pGood : 1.0 - pGood;
}

double P_A_given_I(const string& a, const string& i) {
    double pGood;
    if      (i == "High") pGood = 0.8;
    else if (i == "Low")  pGood = 0.3;
    else return 0.0;
    return (a == "Good") ? pGood : 1.0 - pGood;
}

double jointProbability(const string& d, const string& i,
                        const string& g, const string& a) {
    return P_D(d) * P_I(i) * P_G_given_DI(g, d, i) * P_A_given_I(a, i);
}

double marginalSum(const string& d, const string& i,
                   const string& g, const string& a) {
    vector<string> Dvals = (d.empty()) ? vector<string>{"Easy","Hard"} : vector<string>{d};
    vector<string> Ivals = (i.empty()) ? vector<string>{"High","Low"}  : vector<string>{i};
    vector<string> Gvals = (g.empty()) ? vector<string>{"Good","Poor"} : vector<string>{g};
    vector<string> Avals = (a.empty()) ? vector<string>{"Good","Poor"} : vector<string>{a};

    double total = 0.0;
    for (auto& dv : Dvals)
        for (auto& iv : Ivals)
            for (auto& gv : Gvals)
                for (auto& av : Avals)
                    total += jointProbability(dv, iv, gv, av);
    return total;
}

void result(const string& query, double val) {
    cout << fixed << setprecision(4);
    cout << "  " << query << " = " << val << "\n";
}

int main() {
    cout << "\n  P(D,I,G,A) = P(D) x P(I) x P(G|D,I) x P(A|I)\n\n";
    cout << "  D     I      G     A      P(D,I,G,A)\n";
    cout << "  " << string(50,'-') << "\n";

    double totalCheck = 0.0;
    for (auto& d : {"Easy","Hard"})
        for (auto& i : {"High","Low"})
            for (auto& g : {"Good","Poor"})
                for (auto& a : {"Good","Poor"}) {
                    double p = jointProbability(d,i,g,a);
                    totalCheck += p;
                    cout << fixed << setprecision(4);
                    cout << "  " << setw(5) << left << d
                         << setw(6) << left << i
                         << setw(6) << left << g
                         << setw(6) << left << a
                         << p << "\n";
                }
    cout << "  " << string(50,'-') << "\n";
    cout << "  Sum of all joint probabilities = " << totalCheck << " (should be 1.0)\n";
    double P_evidence = marginalSum("Easy","High","","");
    cout << "\n  P(D=Easy, I=High) = " << fixed << setprecision(4) << P_evidence << "\n\n";
    double P_G_good_given_evidence = marginalSum("Easy","High","Good","") / P_evidence;
    result("P(G=Good | D=Easy, I=High)", P_G_good_given_evidence);
    double P_G_poor_given_evidence = marginalSum("Easy","High","Poor","") / P_evidence;
    result("P(G=Poor | D=Easy, I=High)", P_G_poor_given_evidence);
    double P_A_good_given_evidence = marginalSum("Easy","High","","Good") / P_evidence;
    result("P(A=Good | D=Easy, I=High)", P_A_good_given_evidence);
    double P_A_poor_given_evidence = marginalSum("Easy","High","","Poor") / P_evidence;
    result("P(A=Poor | D=Easy, I=High)", P_A_poor_given_evidence);
    double P_GA_good = marginalSum("Easy","High","Good","Good") / P_evidence;
    result("P(G=Good, A=Good | D=Easy, I=High)", P_GA_good);
    cout << "\n  [Cross-check via CPT direct lookup]\n";
    result("P(G=Good|D=Easy,I=High) direct", P_G_given_DI("Good","Easy","High"));
    result("P(A=Good|I=High)        direct", P_A_given_I("Good","High"));

    // 4a) P(G=Good | I=High)  -- marginalise over D
    cout << "\n  [4a] P(G=Good | I=High)  -- marginalise over Difficulty\n";
    double P_IHigh = marginalSum("","High","","");
    double P_G_good_IHigh = marginalSum("","High","Good","") / P_IHigh;
    result("P(G=Good | I=High)", P_G_good_IHigh);
    cout << "  Breakdown:\n";
    for (auto& d : {"Easy","Hard"}) {
        double contrib = P_D(d) * P_G_given_DI("Good", d, "High");
        cout << "    P(D=" << d << ") * P(G=Good|D=" << d
             << ",I=High) = " << P_D(d) << " * "
             << P_G_given_DI("Good",d,"High") << " = "
             << fixed << setprecision(4) << contrib << "\n";
    }
    cout << "\n  [4b] P(I=High | G=Good)  -- Bayes' theorem\n";
    double P_G_good      = marginalSum("","","Good","");
    double P_G_good_IH   = marginalSum("","High","Good","");
    double P_I_high_given_Ggood = P_G_good_IH / P_G_good;
    result("P(G=Good)              (marginal)", P_G_good);
    result("P(G=Good, I=High)                ", P_G_good_IH);
    result("P(I=High | G=Good)               ", P_I_high_given_Ggood);
    cout << "\n  [4c] P(G=Good | D=Hard, I=Low)\n";
    result("P(G=Good | D=Hard, I=Low)", P_G_given_DI("Good","Hard","Low"));
    cout << "\n  [4d] P(A=Good | G=Good)  -- marginalise over I and D\n";
    double P_G_good2     = marginalSum("","","Good","");
    double P_GA_good2    = marginalSum("","","Good","Good");
    double P_A_good_given_Ggood = P_GA_good2 / P_G_good2;
    result("P(A=Good, G=Good)  ", P_GA_good2);
    result("P(G=Good)          ", P_G_good2);
    result("P(A=Good | G=Good) ", P_A_good_given_Ggood);
    cout << "\n  [4e] Marginal P(G=Good)  -- sum over all D, I, A\n";
    result("P(G=Good)", marginalSum("","","Good",""));
    result("P(G=Poor)", marginalSum("","","Poor",""));
    cout << "\n  [4f] Marginal P(A=Good)  -- sum over all D, I, G\n";
    result("P(A=Good)", marginalSum("","","","Good"));
    result("P(A=Poor)", marginalSum("","","","Poor"));

    return 0;
}