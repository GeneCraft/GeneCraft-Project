#include "experimentspropertiescontroller.h"
#include "ui_experimentspropertiescontroller.h"

#include "floatmutationcontroller.h"

ExperimentsPropertiesController::ExperimentsPropertiesController(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ExperimentsPropertiesController)
{
    ui->setupUi(this);

    // Body
    FloatMutationController *boneLengthMutation = new FloatMutationController("Bones Length");
    FloatMutationController *boneRadiusMutation = new FloatMutationController("Bones Radius");
    FloatMutationController *fixationRadiusMutation = new FloatMutationController("Fixations Radius");
    FloatMutationController *boneAngularOrigin = new FloatMutationController("Bones angular origin");

    ui->vlBodyMutations->addWidget(boneLengthMutation);
    ui->vlBodyMutations->addWidget(boneRadiusMutation);
    ui->vlBodyMutations->addWidget(fixationRadiusMutation);
    ui->vlBodyMutations->addWidget(boneAngularOrigin);

    // Brain
    FloatMutationController *brainInPos = new FloatMutationController("BrainIn Position");
    FloatMutationController *brainInWeight = new FloatMutationController("BrainIn Weight");
    FloatMutationController *constValue = new FloatMutationController("Constant Value");

    ui->vlBrainMutations->addWidget(brainInPos);
    ui->vlBrainMutations->addWidget(brainInWeight);
    ui->vlBrainMutations->addWidget(constValue);

    // Buttons
    connect(ui->pbSave,SIGNAL(clicked()),this,SLOT(save()));
    connect(ui->pbClose,SIGNAL(clicked()),this,SLOT(close()));
}

ExperimentsPropertiesController::~ExperimentsPropertiesController()
{
    delete ui;
}

void ExperimentsPropertiesController::save(){

    // TODO...

    close();
}
