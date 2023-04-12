#pragma once
#include"pch.h"
#include"process.h"
#include"pefile.h"
struct IatInfo
{
	uint64_t		addr;				//Ҫ�޸���λ��
	EDirection		direct;				//�ж���1+5����5+1
	ECommandType	origin_mnemonic;	//ԭʼָ�� call,mov,jmp
	x86_reg			api_reg;			//���api��ַ�ļĴ���
	uint64_t		api_addr;			//api��ַ
	std::string		api_module;			//apiģ����
	std::string		api_name;			//api������
	uint32_t		fix_offset;			//����ַ���޸���ַ�����λ��
};

class iat
{
private:
	uc_engine* m_uc;
	REGS m_regs;
	csh m_cshandle;
	mem::Process m_Process;
	std::unique_ptr<pe> m_pe;
	std::string m_targetModule;

	void write_regs(REGS regs);
	REGS read_regs();
public:
	iat(uint32_t pid, std::string module_name);
	~iat();
	std::vector<uint64_t> search_IAT(uint64_t code_begin, uint64_t code_size, uint64_t vmp0_begin, uint64_t vmp0_size);
	std::vector<IatInfo> process_IAT(std::vector<uint64_t> iats);
	bool fix_IAT(std::vector<IatInfo>& iatInfos);
	bool fix_Dump(uint32_t rva_oep, std::vector<IatInfo> iatList, std::string output);
};