#define DLG_ABOUNT

// 用于应用程序“关于”菜单项的 CDlgAbout 对话框
class CDlgAbout : public CDialogEx										\
{																		\
public:																	\
	CDlgAbout();														\

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };										\

protected:																\

	// DDX/DDV 支持
	virtual void DoDataExchange(CDataExchange* pDX);					\

	// 实现
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