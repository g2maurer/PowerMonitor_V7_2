//////////////////////////////////////////////////////
//
//
#define MENU_STACK_SIZE 16
int menuStack[MENU_STACK_SIZE];
int menuStkPtr = 0;
//
//
//
//void emptyMenuStack(void)
//{
//  menuStkPtr = 0;
//}

////////////////////////////////////////
//
//  pushMenu
//
void pushMenu(int newMenu)
{
  if (menuStkPtr < MENU_STACK_SIZE)
  {
#ifdef PUSH_POP_DEBUG
    Serial.print(menuStkPtr);
    Serial.print("  PUSH  ");
    Serial.println(menu);
#endif
    menuStack[menuStkPtr++] = menuState;
    menuState = newMenu;
    drawMenu(menuState);
  }
  else
  {
    Serial.println("Menu stack overflow");
    //sysLog("Menu stack overflow");
    // Dump Stack
    for (int i = 0; i < MENU_STACK_SIZE; i++)
    {
      Serial.printf("%d = %d\r\n", i, menuStack[i]);
    }
    delay(2000);
    ESP.restart();
    while (1);
  }
}

////////////////////////////////////
//
//  popMenu
//
void popMenu(void)
{
  if (menuStkPtr > 0)
  {
#ifdef PUSH_POP_DEBUG
    Serial.print(menuStkPtr);
#endif
    --menuStkPtr;
#ifdef PUSH_POP_DEBUG
    Serial.print("  POP  ");
    Serial.println(menuStack[menuStkPtr]);
#endif
    menuState = menuStack[menuStkPtr];
    drawMenu(menuState);
  }
  else
  {
    Serial.println("Menu stack underflow");
    //sysLog("Menu stack underflow");
    // Dump Stack
    for (int i = 0; i < MENU_STACK_SIZE; i++)
    {
      Serial.printf("%d = %d\r\n", i, menuStack[i]);
    }
    delay(2000);
    ESP.restart();
    while (1);
  }
}
