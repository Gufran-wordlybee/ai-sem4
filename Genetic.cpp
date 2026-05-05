#include<iostream>
#include<vector>
#include<cstdlib>
#include<ctime>
#include<algorithm>
using namespace std;
#define N        8    
#define POP_SIZE 25   
#define MAX_GEN  1000 
#define MUT_RATE 20   
typedef vector<int> Chromosome;
int fitness(Chromosome& c){
    int conflicts = 0;
    for(int i = 0; i < N; i++){
        for(int j = i+1; j < N; j++){
            if(c[i] == c[j])               conflicts++; 
            if(abs(c[i]-c[j]) == abs(i-j)) conflicts++; 
        }
    }
    return 28 - conflicts;
}

void printBoard(Chromosome& c){
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(c[j] == i) cout << "Q ";
            else          cout << ". ";
        }
        cout << endl;
    }
}

Chromosome randomChromosome(){
    Chromosome c(N);
    for(int i = 0; i < N; i++)
        c[i] = rand() % N;
    return c;
}

Chromosome select(vector<Chromosome>& pop){
    int total = 0;
    for(auto& c : pop) total += fitness(c);

    int pick = rand() % total;
    int sum  = 0;
    for(auto& c : pop){
        sum += fitness(c);
        if(sum >= pick) return c;
    }
    return pop.back();
}

Chromosome crossover(Chromosome& p1, Chromosome& p2){
    int point = rand() % N;           // crossover point
    Chromosome child(N);
    for(int i = 0; i < N; i++){
        if(i < point) child[i] = p1[i];
        else child[i] = p2[i];
    }
    return child;
}

void mutate(Chromosome& c){
    if(rand() % 100 < MUT_RATE){
        int col = rand() % N;
        c[col]  = rand() % N;        
    }
}
int main(){
    srand(time(0));
    vector<Chromosome> pop(POP_SIZE);
    for(int i = 0; i < POP_SIZE; i++)
        pop[i] = randomChromosome();
    cout << "Population size : " << POP_SIZE << endl;
    cout << "Mutation rate   : " << MUT_RATE << "%" << endl;
    cout << "Max generations : " << MAX_GEN  << endl;
    int gen = 0;
    Chromosome best;
    while(gen < MAX_GEN){
        // sort by fitness descending
        sort(pop.begin(), pop.end(), [](Chromosome& a, Chromosome& b){
            return fitness(a) > fitness(b);
        });
        best = pop[0];
        if(fitness(best) == 28) break;
        vector<Chromosome> newPop;
        newPop.push_back(pop[0]);
        newPop.push_back(pop[1]);

        while((int)newPop.size() < POP_SIZE){
            Chromosome p1    = select(pop);
            Chromosome p2    = select(pop);
            Chromosome child = crossover(p1, p2);
            mutate(child);
            newPop.push_back(child);
        }

        pop = newPop;
        gen++;
    }

    cout << "\nSolved in generation: " << gen << endl;
    cout << "Fitness: " << fitness(best) << "/28" << endl;
    cout << "Conflicts: " << 28 - fitness(best) << endl;
    cout << "\nFinal Board:" << endl;
    printBoard(best);

    return 0;
}