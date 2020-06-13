#pragma once

///
/// An opem file/folder dialog.
///

class OpenFileDialog final
{

	public:

		///
		/// The constructor.
		///

		OpenFileDialog(bool const & openFolder = false);

		///
		/// The destructor.
		///

		~OpenFileDialog();

		///
		/// View the retrived path.
		///

		std::filesystem::path const & ViewPath() const;

		///
		/// Shows the dialog.
		///

		void Show();

	private:

		///
		/// The dialog.
		///

		IFileOpenDialog * _dialog = nullptr;

		///
		/// The retrieved file/folder path.
		///

		std::filesystem::path _path;

};