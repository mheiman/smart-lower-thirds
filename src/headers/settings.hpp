#pragma once

#include <QDialog>
#include <QString>

class QLabel;
class QPushButton;
class QLineEdit;
class QComboBox;
class QPlainTextEdit;
class QColor;
class QDialogButtonBox;
class QFontComboBox;
class QFont;
class QKeySequenceEdit;
class QKeySequence;

class LowerThirdSettingsDialog : public QDialog {
	Q_OBJECT
public:
	explicit LowerThirdSettingsDialog(QWidget *parent = nullptr);
	~LowerThirdSettingsDialog() override;

	void setLowerThirdId(const QString &id);

private slots:
	// Actions
	void onPickBgColor();
	void onPickTextColor();
	void onBrowseProfilePicture();
	void onSaveAndApply();

	// Template tools
	void onImportTemplateClicked();
	void onExportTemplateClicked();
	void onOpenHtmlEditorDialog();
	void onOpenCssEditorDialog();

	// Change handlers
	void onAnimInChanged(int index);
	void onAnimOutChanged(int index);
	void onLtPosChanged(int index);
	void updateCustomAnimFieldsVisibility();

	void onFontChanged(const QFont &font);
	void onHotkeyChanged(const QKeySequence &seq);

private:
	void loadFromState();
	void saveToState();

	void updateColorButton(QPushButton *btn, const QColor &color);
	void openTemplateEditorDialog(const QString &title, QPlainTextEdit *sourceEdit);

private:
	QString currentId;

	// Content
	QLineEdit *titleEdit = nullptr;
	QLineEdit *subtitleEdit = nullptr;

	// Media
	QLineEdit *profilePictureEdit = nullptr;
	QPushButton *browseProfilePictureBtn = nullptr;
	QString pendingProfilePicturePath;

	// Anim/style
	QComboBox *animInCombo = nullptr;
	QComboBox *animOutCombo = nullptr;
	QLabel *customAnimInLabel = nullptr;
	QLineEdit *customAnimInEdit = nullptr;
	QLabel *customAnimOutLabel = nullptr;
	QLineEdit *customAnimOutEdit = nullptr;

	QFontComboBox *fontCombo = nullptr;
	QComboBox *ltPosCombo = nullptr;

	QPushButton *bgColorBtn = nullptr;
	QPushButton *textColorBtn = nullptr;

	// Behavior
	QKeySequenceEdit *hotkeyEdit = nullptr;
	QPushButton *clearHotkeyBtn = nullptr;

	// Templates
	QPlainTextEdit *htmlEdit = nullptr;
	QPlainTextEdit *cssEdit = nullptr;

	// Bottom
	QDialogButtonBox *buttonBox = nullptr;

	// Import/export buttons
	QPushButton *importBtn = nullptr;
	QPushButton *exportBtn = nullptr;

	// Expand buttons
	QPushButton *expandHtmlBtn = nullptr;
	QPushButton *expandCssBtn = nullptr;

	// Colors
	QColor *currentBgColor = nullptr;
	QColor *currentTextColor = nullptr;
};
