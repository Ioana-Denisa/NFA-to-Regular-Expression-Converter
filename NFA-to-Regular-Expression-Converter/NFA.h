#pragma once
#include<iostream>
#include <fstream>
#include<unordered_set>
#include<unordered_map>
#include <cstdlib>




struct PairHash {
    template <typename T1, typename T2>
    std::size_t operator () (const std::pair<T1, T2>& p) const {
        auto h1 = std::hash<T1>{}(p.first);
        auto h2 = std::hash<T2>{}(p.second);


        return h1 ^ h2;
    }
};

struct PairEqual {
    template <typename T1, typename T2>
    bool operator () (const std::pair<T1, T2>& lhs, const std::pair<T1, T2>& rhs) const {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};


class NFA
{
    public:
        NFA();
        NFA(const char& character);
      
        std::unordered_set<std::string> getStates() const;
        std::unordered_set<std::string> getAlphabet() const;
        std::unordered_map<std::pair<std::string, std::string>, std::string, PairHash, PairEqual> getTransitions() const;
        std::string getInitialState() const;
        std::vector< std::string> getFinalState() const;

        void readFile();
        void addStateForStates(const std::string state);
        void addCharacterForAlphabet(const std::string alph);
        void addTransition(const std::string state1, const std::string alph, const std::string state2);

        void printAutomaton();
        void printTransitions();

        void addNewInitialState();
        void addNewFinalState();
        void updateAutomaton();
        int generatedRandomNumber();
        std::string getRandomState();

        std::vector<std::string > getStatesEnterInState(std::string& state);
        std::vector<std::string > getStatesOutOfState(std::string& state);


        std::string getTransitionToStates(std::string& stateIn, std::string& state);
        std::string getTransitionStateToState(std::string& state);
        std::string getTransitionStateToStateOut(std::string& state, std::string& stateOut);

        std::string getExpresion(std::string& stateIn, std::string& state, std::string& stateOut);
        void concatenateTransition(std::string& stateIn, std::string& state);
           
        void removeState(std::vector<std::string>& statesIn, std::vector<std::string>& statesOut, std::string& state);
        void simplifyAutomaton();
        std::string getRegularExpresion();
        std::string getRegularExpresionOnInitialStates();



    private:
        std::unordered_set<std::string> m_states;
        std::unordered_set<std::string> m_alphabet;
        std::unordered_map<std::pair<std::string, std::string>, std::string, PairHash, PairEqual> m_transitions;
        std::string m_initialState;
        std::vector< std::string> m_finalStates;
        std::string const m_lambda= "$";

};

