#ifndef ABSTRACTEDITOR_P_H
#define ABSTRACTEDITOR_P_H

class AbstractField;

class AbstractEditorPrivate
{
	explicit AbstractEditorPrivate();

	AbstractField *field;

	friend class AbstractEditor;
};

#endif // ABSTRACTEDITOR_P_H
