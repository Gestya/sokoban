// TODO : add "include" : "file"
static const char* JSON = R"json(
{
    "RestartWindow" : {
        "type" : "window",
        "position" : [1998, 50],
        "size" : [512, 128],
        "widgets" : {
            "RestartBtn" : {
                "type" : "button",
                "position" : [0, 0],
                "size" : [512, 128],
                "normal" : {
                    "name" : "restart.png", "position" : [0, 0], "size" : [512, 128]
                },
                "pressed" : {
                    "name" : "restart.png", "position" : [0, 128], "size" : [512, 128]
                },
                "disabled" : {
                    "name" : "restart.png", "position" : [0, 256], "size" : [512, 128]
                },
                "command" : "ui.confirm.show"
            }
        }
    },

    "WinningWindow" : {
        "type" : "window",
        "position" : [50, 1130],
        "size" : [1200, 492],
        "visible" : false,
        "widgets" : {
            "Win" : {
                "type" : "image",
                "position" : [0, 0],
                "size" : [1200, 492],
                "sprite" : {
                    "name" : "win.png", "position" : [0, 0], "size" : [512, 512]
                }
            }
        }
    },

    "ConfirmWindow" : {
        "type" : "window",
        "position" : [768, 580],
        "size" : [1024, 512],
        "visible" : false,
        "widgets" : {
            "Background" : {
                "type" : "image",
                "position" : [0, 0],
                "size" : [1024, 512],
                "sprite" : {
                    "name" : "are_you_sure.png", "position" : [0, 0], "size" : [1024, 512]
                }
            },
            "YesBtn" : {
                "type" : "button",
                "position" : [221, 340],
                "size" : [256, 128],
                "normal" : {
                    "name" : "yes_no.png", "position" : [0, 0], "size" : [256, 128]
                },
                "pressed" : {
                    "name" : "yes_no.png", "position" : [0, 128], "size" : [256, 128]
                },
                "disabled" : {
                    "name" : "yes_no.png", "position" : [0, 256], "size" : [256, 128]
                },
                "command" : "ui.confirm.yes"
            },
            "NoBtn" : {
                "type" : "button",
                "position" : [547, 340],
                "size" : [256, 128],
                "normal" : {
                    "name" : "yes_no.png", "position" : [256, 0], "size" : [256, 128]
                },
                "pressed" : {
                    "name" : "yes_no.png", "position" : [256, 128], "size" : [256, 128]
                },
                "disabled" : {
                    "name" : "yes_no.png", "position" : [256, 256], "size" : [256, 128]
                },
                "command" : "ui.confirm.no"
            }
        }
    }
}

)json";