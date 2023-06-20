# Sokoban
Sokoban Game (Android version)

## TODO List
### UI
- [ ] UI initialization: remaster it from returning bool to exceptions.
- [ ] Обмежити рендерінг віджетів у вікні розмірами цього вікна (обрізати все, що стирчить за край вікна).
- [x] ui::Widget::draw() -> ui::Widget::draw(std::vector<Sprite>& sprites).
      І нехай десктоп лізе в рендерер і отримує звідти вектор для спрайтів.
      А всі контроли нехай нічого не знають про рендерер.
- [ ] Вивантаження вікон в UI: всі діти мусять ресетитись.
- [ ] ui::Window must have mouse_transparent attribure.
- [ ] ui::Desktop::CapturedWidget -- look like a right approach but terrible implementation!
- [ ] Opacity for widgets and alpha foor sprites.
- [ ] ui::Widget - треба всі три події від миші об'єднати в одну, тому що суцільан копіпаста!
### General
- [ ] Levels to dat files.
- [ ] Shaders to glsl files.
- [ ] UI to json files.
- [ ] Go to next level / Go to prev level.
- [ ] Move the texture manager from renderer to the separate class.
- [ ] Додати *{ }* на всі оператори в один рядок
- [ ] Отой прикол, щоб subscribe міг викликати тільки нащадок, а із зовні б це було заборонено.
### Command Manager
- [ ] Command must be void/string/float/int/vecX.
- [ ] Для CommandManager зробити Command, Variable, Signal.
- [ ] Для CommandManager::Signal мусить бути мультімапа - кожен сигнал може мати будь яку кількість слухачів.
- [ ] Для команд зробити прапор Wait. Той, хто посилажє команду, може зробити це раніше ніж команда взагалі створена.
      В цьому випадку відправлена команда може знаходитись у буфері і чекати, коли обробника буде додано. 
- [ ] В код додати два сигнали game.start та game.win (хоча треба це? хз).
### Task Manager
- [ ] Зробини Iterators якось по уму, щоб не треба було копіпастити код. І перейменувати їх на щось путнє.

### What is this? Why?!
```
void EventManager::sendMouseEvent(MouseEventType type, const MouseEvent& event) {
    static constexpr float KX = 2560.f / 2558.f;
    static constexpr float KY = 1672.f / 1798.f;

    auto normalizedEvent{event};
    normalizedEvent.x *= KX;
    normalizedEvent.y *= KY;
```

### Can it be useful? Need to think
```
    commandManager->registerCommand("camera.Z", this, CommandManager::Executor(&Camera::onCameraZ));


    typedef<class T>
    commandManager->registerCommand("camera.Z", this, CommandManager::Executor(T& ___));

```


