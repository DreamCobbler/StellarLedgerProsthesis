#include <Precompiled Headers.hpp>

#include <UI/Dialogs/OpenFileDialog.hpp>

OpenFileDialog::OpenFileDialog(bool const & openFolder)
{

	CoCreateInstance(
		CLSID_FileOpenDialog,
		0,
		CLSCTX_INPROC_SERVER,
		IID_PPV_ARGS(&_dialog)
	);

	if (openFolder)
	{

		DWORD options;
		_dialog->GetOptions(&options);

		options |= FOS_PICKFOLDERS;
		_dialog->SetOptions(options);

	}

}

OpenFileDialog::~OpenFileDialog()
{

	_dialog->Release();

}

std::filesystem::path const & OpenFileDialog::ViewPath() const
{

	return _path;

}

void OpenFileDialog::Show()
{

	_path.clear();

	if (!_dialog)
		return;

	if (!SUCCEEDED(_dialog->Show(0)))
		return;

	IShellItem * item = nullptr;
	if (!SUCCEEDED(_dialog->GetResult(&item)))
		return;

	PWSTR filePathBuffer;
	item->GetDisplayName(SIGDN_FILESYSPATH, &filePathBuffer);

	_path = filePathBuffer;

	CoTaskMemFree(filePathBuffer);
	item->Release();

}