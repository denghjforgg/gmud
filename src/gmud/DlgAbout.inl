#define DLG_ABOUNT

// ����Ӧ�ó��򡰹��ڡ��˵���� CDlgAbout �Ի���
class CDlgAbout : public CDialogEx										\
{																		\
public:																	\
	CDlgAbout();														\

	// �Ի�������
	enum { IDD = IDD_ABOUTBOX };										\

protected:																\

	// DDX/DDV ֧��
	virtual void DoDataExchange(CDataExchange* pDX);					\

	// ʵ��
protected:																\
	DECLARE_MESSAGE_MAP()												\
};

CDlgAbout::CDlgAbout() : CDialogEx(CDlgAbout::IDD)						\
{																		\
}																		\

void CDlgAbout::DoDataExchange(CDataExchange* pDX)						\
{																		\
	CDialogEx::DoDataExchange(pDX);										\
}																		\

BEGIN_MESSAGE_MAP(CDlgAbout, CDialogEx)									\
END_MESSAGE_MAP()