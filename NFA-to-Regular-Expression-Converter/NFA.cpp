#include "NFA.h"

NFA::NFA()
{
	readFile();
}



std::unordered_set<std::string> NFA::getStates() const
{
	return this->m_states;
}

std::unordered_set<std::string> NFA::getAlphabet() const
{
	return this->m_alphabet;
}

std::unordered_map<std::pair<std::string, std::string>, std::string, PairHash, PairEqual> NFA::getTransitions() const
{
	return this->m_transitions;
}

std::string NFA::getInitialState() const
{
	return this->m_initialState;
}

std::vector<std::string> NFA::getFinalState() const
{
	return this->m_finalStates;
}



void NFA::readFile()
{
	std::ifstream file("file.txt");
	if (!file.is_open())
	{
		std::cout << ("Fisierul nu a putut fii deschis!");
		return;
	}
	std::string state1, state2, alph;
	int dim;
	file >> dim;

	for (int i = 0; i < dim; i++)
	{
		file >> state1 >> state2 >> alph;
		addCharacterForAlphabet(alph);
		addStateForStates(state1);
		addStateForStates(state2);
		addTransition(state1, alph, state2);
	}
	file >> m_initialState;
	file >> dim;
	for (int i = 0; i < dim; i++)
	{
		file >> state1;
		m_finalStates.emplace_back(state1);
	}

	file.close();
}

void NFA::addStateForStates(const std::string state)
{
	if (m_states.empty())
		m_states.insert(state);
	else if (m_states.find(state) == m_states.end())
	{
		m_states.insert(state);
	}
}

void NFA::addCharacterForAlphabet(const std::string alph)
{
	if (m_alphabet.empty())
		m_alphabet.insert(alph);
	else if (m_alphabet.find(alph) == m_alphabet.end())
		m_alphabet.insert(alph);
}

void NFA::addTransition(const std::string state1, const std::string alph, const std::string state2)
{
	if (m_transitions.find({ state1, state2 }) == m_transitions.end())
		m_transitions.insert({ {state1,state2},alph });
	else
	{
		std::string alphabet = m_transitions.at({ state1,state2 });
		alphabet += "+" + alph;
		m_transitions.at({ state1,state2 }) = alphabet;
	}
}

void NFA::printAutomaton()
{
	std::cout << "States: \n";
	for (auto it : m_states)
	{
		std::cout << it << " ";
	}

	std::cout << "\nInitial state: " << m_initialState << "\n";

	std::cout << "Final states: \n";
	for (int i = 0; i < m_finalStates.size(); i++)
	{
		std::cout << m_finalStates[i] << " ";
	}

	std::cout << "Alphabet: \n";
	for (auto it : m_alphabet)
	{
		std::cout << it << " ";
	}

	std::cout << "\nTransitions: \n";
	for (auto it : m_transitions)
	{
		std::cout << "(" << it.first.first << ", " << it.first.second << ")-> " << it.second << "\n";
	}
	std::cout << "\n";
}

void NFA::printTransitions()
{
	std::cout << "\nTransitions: \n";
	for (auto it : m_transitions)
	{
		std::cout << "(" << it.first.first << ", " << it.first.second << ")-> " << it.second << "\n";
	}
	std::cout << "\n";
}

void NFA::addNewInitialState()
{
	std::string newInitialState = "I";
	m_states.insert(newInitialState);
	m_transitions.insert({ {newInitialState,m_initialState },m_lambda });
	m_initialState = newInitialState;
}

void NFA::addNewFinalState()
{
	std::string newFinalState = "F";
	m_states.insert(newFinalState);
	for (int i = 0; i < m_finalStates.size(); i++)
	{
		m_transitions.insert({ {m_finalStates[i],newFinalState}, m_lambda});
	}
	m_finalStates.clear();
	m_finalStates.emplace_back(newFinalState);
}

void NFA::updateAutomaton()
{
	addNewInitialState();
	addNewFinalState();
	std::cout << "Noul automat:\n";
	printAutomaton();
}

int NFA::generatedRandomNumber()
{
	int randomNumber = rand() % m_states.size();
	return randomNumber;
}

std::string NFA::getRandomState()
{
	int index = generatedRandomNumber();
	int i = 0;
	for (std::string state : m_states)
	{
		if (i != index)
			i++;
		else if (i == index && state != m_initialState && state != m_finalStates[0])
			return state;
	}
}

std::vector<std::string> NFA::getStatesEnterInState(std::string& state)
{
	std::vector<std::string> states;
	for (auto transition : m_transitions)
	{
		if (transition.first.second == state)
		{
			auto it = std::find(states.begin(), states.end(), transition.first.first);
			if (it == states.end())
			{
				if (transition.first.first != state)
					states.emplace_back(transition.first.first);
			}
		}
	}

	return states;
}

std::vector<std::string> NFA::getStatesOutOfState(std::string& state)
{
	std::vector<std::string> states;
	for (auto transition : m_transitions)
	{
		if (transition.first.first == state)
		{
			auto it = std::find(states.begin(), states.end(), transition.first.second);
			if (it == states.end())
			{
				if (transition.first.second != state)
					states.emplace_back(transition.first.second);
			}
		}
	}

	return states;
}

std::string NFA::getTransitionToStates(std::string& stateIn, std::string& state)
{
	std::string transitionStates = "";
	int nrTrasition = 0;
	auto it = m_transitions.find({ stateIn,state });
	if (it != m_transitions.end() && it->second != m_lambda)
	{
		transitionStates += it->second;
	}

	if (transitionStates.size() > 1 && (transitionStates.front() != '(' || transitionStates.back() != ')'))
		transitionStates = "(" + transitionStates + ")";

	return transitionStates;
}

std::string NFA::getTransitionStateToState(std::string& state)
{
	std::string transitionStates = "";
	auto it = m_transitions.find({ state,state });
	if (it != m_transitions.end() && it->second != m_lambda)
	{
		if (it->second.size() > 1 && (it->second.front() != '(' || it->second.back() != ')'))
			transitionStates += "(" + it->second + ")*";
		else
		{
			transitionStates += it->second + "*";
		}
	}

	return transitionStates;
}



std::string NFA::getExpresion(std::string& stateIn, std::string& state, std::string& stateOut)
{
	std::string trasnition1 = getTransitionToStates(stateIn, state);
	std::string transition2 = getTransitionStateToState(state);
	std::string transition3 = getTransitionToStates(state, stateOut);
	std::string transition = trasnition1 + transition2 + transition3;
	if (transition == "")
		transition = m_lambda;
	if (transition.size() > 1 && (transition.front() != '(' || transition.back() != ')'))
		return "(" + transition + ")";
	else
		return transition;
}

void NFA::removeState(std::vector<std::string>& statesIn, std::vector<std::string>& statesOut, std::string& state)
{
	for (int i = 0; i < statesIn.size(); i++)
	{
		for (int j = 0; j < statesOut.size(); j++)
		{
			m_transitions.erase({ state,statesOut[j] });
			if (m_transitions.find({ state,state }) != m_transitions.end())
			{
				m_transitions.erase({ state,state });
			}
		}
		m_transitions.erase({ statesIn[i],state });
	}
	m_states.erase(state);
}



void NFA::simplifyAutomaton()
{
	while (m_states.size() > 2)
	{
		std::string state = getRandomState();
		if (state != "")
		{
			std::cout << "Eliminam starea: " << state << "\n";
			std::vector<std::string> statesIn = getStatesEnterInState(state);
			std::vector<std::string>statesOut = getStatesOutOfState(state);

			for (int i = 0; i < statesIn.size(); i++)
			{
				for (int j = 0; j < statesOut.size(); j++)
				{
					std::string expression = getExpresion(statesIn[i], state, statesOut[j]);
					if (m_transitions.find({ statesIn[i],statesOut[j] }) != m_transitions.end())
					{
						m_transitions.at({ statesIn[i],statesOut[j] }) += "+" + expression;
					}
					else
						m_transitions.insert({ {statesIn[i],statesOut[j]},expression });
				}

			}
			removeState(statesIn, statesOut, state);
			printTransitions();
		}
	}
}

std::string NFA::getRegularExpresion()
{
	simplifyAutomaton();
	std::string expression = m_transitions.at({ m_initialState,m_finalStates[0]});


	return expression;
}


