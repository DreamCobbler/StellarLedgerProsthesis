/*
 *
 * Stellar Ledger Prosthesis
 * Copyright (C) 2020 Benedykt Synakiewicz (dreamcobbler@outlook.com)
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <Precompiled Headers.hpp>

#include <Resources/Resources.hpp>

#include <UI/Concepts/Window.hpp>

#include <Configuration.hpp>

Window::Window()
{

	RegisterWindowClass();

}

void Window::Reposition(
	std::optional<int> x,
	std::optional<int> y,
	std::optional<int> width,
	std::optional<int> height
)
{

	if (!_handle)
		return;

	auto const positionChange = x.has_value() || y.has_value();
	auto const sizeChange = width.has_value() || height.has_value();

	SetWindowPos(
		_handle,
		0,
		x.value_or(0),
		y.value_or(0),
		width.value_or(0),
		height.value_or(0),
		SWP_NOACTIVATE | SWP_NOOWNERZORDER | SWP_NOZORDER |
			(positionChange? 0 : SWP_NOMOVE) |
			(sizeChange? 0 : SWP_NOSIZE)
	);

}

void Window::Enable(bool const & enable)
{

	if (!_handle)
		return;

	EnableWindow(_handle, enable? TRUE : FALSE);
	UpdateWindow(_handle);

}

void Window::Show(bool const & show)
{

	if (!_handle)
		return;

	ShowWindow(_handle, show? SW_SHOW : SW_HIDE);

}

void Window::Repaint()
{

	if (!_handle)
		return;

	InvalidateRect(_handle, nullptr, TRUE);
	UpdateWindow(_handle);

}

void Window::RepositionChildren()
{

	RECT clientAreaRectangle;
	GetClientRect(_handle, &clientAreaRectangle);

	OnSize(clientAreaRectangle.right, clientAreaRectangle.bottom);

}

Window::operator HWND const &() const
{

	return _handle;

}

LRESULT CALLBACK Window::WindowProcedure(
	HWND windowHandle,
	UINT message,
	WPARAM wordParameter,
	LPARAM longParameter
)
{

	auto const windowObjectAddress = GetWindowLongPtr(windowHandle, GWLP_USERDATA);
	auto window = reinterpret_cast<Window *>(windowObjectAddress);

	if (window)
		switch (message)
		{

			case WM_COMMAND:
			{

				window->OnCommand(wordParameter);

				return 0;

			}

			case WM_DESTROY:
			{

				window->OnDestroy();

				return 0;

			}

			case WM_ENABLE:
			{

				window->OnEnable(wordParameter? true : false);

				return 0;

			}

			case WM_NOTIFY:
			{

				if (longParameter)
					return window->OnNotify(* reinterpret_cast<NMHDR *>(longParameter));

				return 0;

			}

			case WM_PAINT:
			{

				PAINTSTRUCT paintingData;
				BeginPaint(windowHandle, &paintingData);

				window->OnPaint(paintingData);

				EndPaint(windowHandle, &paintingData);

				return 0;

			}

			case WM_SIZE:
			{

				window->OnSize(LOWORD(longParameter), HIWORD(longParameter));

				return 0;

			}

		}

	return DefWindowProc(windowHandle, message, wordParameter, longParameter);

}

void Window::RegisterWindowClass()
{

	WNDCLASSEX windowClassDefinition = {0};

	windowClassDefinition.cbSize = sizeof(windowClassDefinition);
	windowClassDefinition.style;
	windowClassDefinition.lpfnWndProc = WindowProcedure;
	windowClassDefinition.hIcon = LoadIcon(
		GetModuleHandle(0),
		MAKEINTRESOURCE(IDI_SLP_APPLICATION_ICON)
	);
	windowClassDefinition.hCursor = LoadCursor(0, IDC_ARROW);
	windowClassDefinition.hbrBackground = GetSysColorBrush(COLOR_BTNFACE);
	windowClassDefinition.lpszClassName = WindowClassName.data();
	windowClassDefinition.hIconSm = windowClassDefinition.hIcon;

	RegisterClassEx(&windowClassDefinition);

}

void Window::Create(
	HWND const & parentWindowHandle,
	std::string const & title,
	int const & x,
	int const & y,
	int const & width,
	int const & height
)
{

	_handle = CreateWindowEx(
		WS_EX_COMPOSITED,
		WindowClassName.data(),
		title.data(),
		(parentWindowHandle? WS_CHILD : WS_OVERLAPPEDWINDOW) | WS_CLIPCHILDREN | WS_CLIPSIBLINGS,
		x,
		y,
		width,
		height,
		parentWindowHandle,
		0,
		0,
		0
	);

	SetWindowLongPtr(_handle, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(this));

}