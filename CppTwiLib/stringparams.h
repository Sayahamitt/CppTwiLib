#ifndef STRING_PARAMS_H
#define STRING_PARAMS_H

#include <string>
#include <vector>

class stringparams{
 private:
	typedef struct m_param{
		std::string m_key;
		std::string m_value;
	}m_param;

	std::vector<m_param> m_params;

	static bool comp_params(const m_param &left, const m_param &right);
	
 public:
	stringparams();
	~stringparams();

	stringparams& operator+=(const stringparams& left);

	std::vector<m_param> get_m_params()const;

	void add(std::string key,std::string value);
	void sort_by_key();
	void show();
	void show(int num);

	int size();

	std::vector<std::string> comb_key_value_by(std::string k_mid);
	std::string comb_params_by(std::string k_mid,std::string f_mid);
};

#endif
