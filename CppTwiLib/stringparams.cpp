#include <iostream>
#include <string>
#include <algorithm>

#include "stringparams.h"

stringparams::stringparams(){}

stringparams::~stringparams(){}

stringparams& stringparams::operator+=(const stringparams& left){
	std::vector<m_param> params_buffer;
	params_buffer = left.get_m_params();
	
	for(int i=0;i<left.m_params.size();i++){
		m_params.push_back(params_buffer[i]);
	}
	return *this;
}

std::vector<stringparams::m_param> stringparams::get_m_params()const{
	return m_params;
}

bool stringparams::comp_params(const m_param &left,const m_param &right){
	size_t size;
	bool left_key_is_longer;
	if(left.m_key.size()<right.m_key.size()){
		size=left.m_key.size();
		left_key_is_longer=false;
	}else{
		size=right.m_key.size();
		left_key_is_longer=true;
	}
	
	for(int i=0;i<size;i++){
		if(left.m_key[i]<right.m_key[i]){
			return true;
		}else if(left.m_key[i]>right.m_key[i]){
			return false;
		}
	}
	
	return !left_key_is_longer;
}

void stringparams::add(std::string key,std::string value){
	m_param newfield;
	newfield.m_key = key;
	newfield.m_value =value;

	m_params.push_back(newfield);
}

void stringparams::sort_by_key(){
	std::sort(m_params.begin(),m_params.end(),comp_params);
}

void stringparams::show(){
	for(int i=0;i<m_params.size();i++){
		std::cout<<m_params[i].m_key<<' '<<m_params[i].m_value<<std::endl;
	}
}

void stringparams::show(int num){
	if(num<m_params.size()){
		std::cout<<m_params[num].m_key<<' '<<m_params[num].m_value<<std::endl;
	}
}

int stringparams::size(){
	return (int)m_params.size();
}

std::vector<std::string> stringparams::comb_key_value_by(std::string k_mid){
	std::vector<std::string> fields;

	for(int i=0;i<m_params.size();i++){
		fields.push_back(m_params[i].m_key+k_mid+m_params[i].m_value);
	}

	return fields;
}

std::string stringparams::comb_params_by(std::string k_mid,std::string f_mid){
	int counter;
	std::string conb_hole;
	for(counter=0;counter<m_params.size();counter++){
		conb_hole += m_params[counter].m_key+k_mid+m_params[counter].m_value+f_mid;
	}
	if(counter>0){
		//最後のパラメータの後にもf_midが付いているので、それを削除
		conb_hole.erase(conb_hole.size()-f_mid.size(),conb_hole.size());
	}
	return conb_hole;
}
