#ifndef FLATGUIENUMS_H
#define FLATGUIENUMS_H

namespace FlatGui {
enum TransitionDirection : int {
	TD_In = 0,
	TD_Out
};

enum BoundaryType : int {
	BND_Start = 0,
	BND_End
};

enum DurationType : int {
	DT_Long = 0,
	DT_Normal,
	DT_Short
};
}

#endif // FLATGUIENUMS_H
