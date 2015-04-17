// QR_Encode.h : CQR_Encode �N���X�錾����уC���^�[�t�F�C�X��`
// Date 2006/05/17	Ver. 1.22	Psytec Inc.

#if !defined(AFX_QR_ENCODE_H__AC886DF7_C0AE_4C9F_AC7A_FCDA8CB1DD37__INCLUDED_)
#define AFX_QR_ENCODE_H__AC886DF7_C0AE_4C9F_AC7A_FCDA8CB1DD37__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

/////////////////////////////////////////////////////////////////////////////
#include <windows.h>

// ���������x��
#define QR_LEVEL_L	0
#define QR_LEVEL_M	1
#define QR_LEVEL_Q	2
#define QR_LEVEL_H	3

// �f�[�^���[�h
#define QR_MODE_NUMERAL		0
#define QR_MODE_ALPHABET	1
#define QR_MODE_8BIT		2
#define QR_MODE_KANJI		3

// �o�[�W����(�^��)�O���[�v
#define QR_VRESION_S	0 // 1 �` 9
#define QR_VRESION_M	1 // 10 �` 26
#define QR_VRESION_L	2 // 27 �` 40

#define MAX_ALLCODEWORD	 3706 // ���R�[�h���[�h���ő�l
#define MAX_DATACODEWORD 2956 // �f�[�^�R�[�h���[�h�ő�l(�o�[�W����40-L)
#define MAX_CODEBLOCK	  153 // �u���b�N�f�[�^�R�[�h���[�h���ő�l(�q�r�R�[�h���[�h���܂�)
#define MAX_MODULESIZE	  177 // ��Ӄ��W���[�����ő�l

// �r�b�g�}�b�v�`�掞�}�[�W��
#define QR_MARGIN	4


/////////////////////////////////////////////////////////////////////////////
typedef struct tagRS_BLOCKINFO
{
	int ncRSBlock;
	int ncAllCodeWord;
	int ncDataCodeWord;

} RS_BLOCKINFO, *LPRS_BLOCKINFO;


/////////////////////////////////////////////////////////////////////////////
// QR�R�[�h�o�[�W����(�^��)�֘A���

typedef struct tagQR_VERSIONINFO
{
	int nVersionNo;
	int ncAllCodeWord;

	// �ȉ��z��Y���͌�������(0 = L, 1 = M, 2 = Q, 3 = H) 
	int ncDataCodeWord[4];

	int ncAlignPoint;
	int nAlignPoint[6];

	RS_BLOCKINFO RS_BlockInfo1[4];
	RS_BLOCKINFO RS_BlockInfo2[4];

} QR_VERSIONINFO, *LPQR_VERSIONINFO;


/////////////////////////////////////////////////////////////////////////////
// CQR_Encode �N���X

class CQR_Encode
{
public:
	CQR_Encode();
	~CQR_Encode();

public:
	int m_nLevel;
	int m_nVersion;
	BOOL m_bAutoExtent;
	int m_nMaskingNo;

public:
	int m_nSymbleSize;
	BYTE m_byModuleData[MAX_MODULESIZE][MAX_MODULESIZE];
	// bit5:�@�\���W���[���i�}�X�L���O�ΏۊO�j�t���O
	// bit4:�@�\���W���[���`��f�[�^
	// bit1:�G���R�[�h�f�[�^
	// bit0:�}�X�N��G���R�[�h�`��f�[�^
	

private:
	int m_ncDataCodeWordBit;
	BYTE m_byDataCodeWord[MAX_DATACODEWORD];

	int m_ncDataBlock;
	BYTE m_byBlockMode[MAX_DATACODEWORD];
	int m_nBlockLength[MAX_DATACODEWORD];

	int m_ncAllCodeWord;
	BYTE m_byAllCodeWord[MAX_ALLCODEWORD];
	BYTE m_byRSWork[MAX_CODEBLOCK];

public:
	BOOL EncodeData(int nLevel, int nVersion, BOOL bAutoExtent, int nMaskingNo, LPCSTR lpsSource, int ncSource = 0);

private:
	int GetEncodeVersion(int nVersion, LPCSTR lpsSource, int ncLength);
	BOOL EncodeSourceData(LPCSTR lpsSource, int ncLength, int nVerGroup);

	int GetBitLength(BYTE nMode, int ncData, int nVerGroup);

	int SetBitStream(int nIndex, WORD wData, int ncData);

	BOOL IsNumeralData(unsigned char c);
	BOOL IsAlphabetData(unsigned char c);
	BOOL IsKanjiData(unsigned char c1, unsigned char c2);

	BYTE AlphabetToBinaly(unsigned char c);
	WORD KanjiToBinaly(WORD wc);

	void GetRSCodeWord(LPBYTE lpbyRSWork, int ncDataCodeWord, int ncRSCodeWord);

private:
	void FormatModule();

	void SetFunctionModule();
	void SetFinderPattern(int x, int y);
	void SetAlignmentPattern(int x, int y);
	void SetVersionPattern();
	void SetCodeWordPattern();
	void SetMaskingPattern(int nPatternNo);
	void SetFormatInfoPattern(int nPatternNo);
	int CountPenalty();
};

/////////////////////////////////////////////////////////////////////////////

#endif // !defined(AFX_QR_ENCODE_H__AC886DF7_C0AE_4C9F_AC7A_FCDA8CB1DD37__INCLUDED_)
