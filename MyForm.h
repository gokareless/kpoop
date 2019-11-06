#pragma once

namespace kpoop {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Data::SqlServerCe;
	using namespace System::IO;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			int w = 0;
			for (int i = 0; i < listView1->Columns->Count; i++)
			{
				w += listView1->Columns[i]->Width;
			}
			if (listView1->BorderStyle == BorderStyle::Fixed3D)
				w += 4;
			listView1->Width = w + 17;
			//
			//TODO: Add the constructor code here
			//
		}
	private:
		String^ dbf;
		String^ stDataSource;

	private: void ShowDb()
	{
		SqlCeEngine^ engine = gcnew SqlCeEngine(stDataSource);
		SqlCeConnection^ connection = gcnew SqlCeConnection(engine->LocalConnectionString);
		connection->Open();
		SqlCeCommand^ command = connection->CreateCommand();
		command->CommandText = "SELECT * FROM Albums";
		SqlCeDataReader^ dataReader = command->ExecuteReader();

		String^ st;
		int itemIndex = 0;

		listView1->Items->Clear();

		while (dataReader->Read())
		{
			for (int i = 0; i < dataReader->FieldCount; i++)
			{
				st = dataReader->GetValue(i)->ToString();
				switch (i)
				{
				case 0:
					listView1->Items->Add(st);
					break;
				case 1:
					listView1->Items[itemIndex]->SubItems->Add(st);
					break;
				case 2:
					listView1->Items[itemIndex]->SubItems->Add(st);
					break;
				};
			}
			itemIndex++;
		}
		connection->Close();
	}

	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e)
	{
		SqlCeEngine^ engine;
		String^ dbf = "catalog.sdf";
		stDataSource = "Data Source='" + dbf + "';";
		engine = gcnew SqlCeEngine(stDataSource);
		ShowDb();
	}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListView^ listView1;
	private: System::Windows::Forms::ColumnHeader^ columnHeader1;
	private: System::Windows::Forms::ColumnHeader^ columnHeader2;
	private: System::Windows::Forms::ColumnHeader^ columnHeader3;
	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->listView1 = (gcnew System::Windows::Forms::ListView());
			this->columnHeader1 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader2 = (gcnew System::Windows::Forms::ColumnHeader());
			this->columnHeader3 = (gcnew System::Windows::Forms::ColumnHeader());
			this->SuspendLayout();
			// 
			// listView1
			// 
			this->listView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(3) {
				this->columnHeader1, this->columnHeader2,
					this->columnHeader3
			});
			this->listView1->FullRowSelect = true;
			this->listView1->GridLines = true;
			this->listView1->HideSelection = false;
			this->listView1->Location = System::Drawing::Point(39, 43);
			this->listView1->MultiSelect = false;
			this->listView1->Name = L"listView1";
			this->listView1->Size = System::Drawing::Size(234, 113);
			this->listView1->TabIndex = 0;
			this->listView1->UseCompatibleStateImageBehavior = false;
			this->listView1->View = System::Windows::Forms::View::Details;
			// 
			// columnHeader1
			// 
			this->columnHeader1->Text = L"cid";
			this->columnHeader1->Width = 35;
			// 
			// columnHeader2
			// 
			this->columnHeader2->Text = L"name";
			this->columnHeader2->Width = 130;
			// 
			// columnHeader3
			// 
			this->columnHeader3->Text = L"songs";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(347, 261);
			this->Controls->Add(this->listView1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}
