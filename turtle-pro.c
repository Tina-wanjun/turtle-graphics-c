/**
 * CSC A48 - Intro to Computer Science II
 * 
 * This is the program file where you will implement your solution for
 * assignment 1. Please make sure you read through this file carefully
 * and that you understand what is provided and what you need to complete.
 * 
 * You will need to have read the handout carefully. Parts where you have to 
 * implement functionality are clearly labeled TODO.
 * 
 * Be sure to test your work thoroughly, our testing will be extensive and will
 * check that your solution is *correct*, not only that it provides 
 * functionality.
 * 
 * Developed by Mustafa Quraish for CSCA48
 * (c) Mustafa Quraish
 */
#include "imgUtils.c"

// This lets the driver code override the image size if it needs to. Make sure 
// you don't hard-code these values anywhere!
#ifndef SIZEX
  #define SIZEX 512
  #define SIZEY 512
#endif 

/*---------------------------------------------------------------------------*/

/**
 * This struct contains one node of the linked list, which represents a single 
 * command to the Turtle. It's field should include:
 * 
 *  - cmd   : A char array of size 10 holding the command name
 * 
 *  - val   : An integer that stores a parameter for the command (like forward,
 *            backward and colour). 
 * 
 *  - next  : A pointer to a struct of the same type, this is used for the 
 *            linked list
 * 
 * TODO: Complete this struct definition
 ****/

typedef struct cmdnode {
  char cmd[10];
  int val;
  struct cmdnode *loop_head;
  struct cmdnode *next;
} CmdNode;

/*---------------------------------------------------------------------------*/

int validCmd(char cmd[10]){
  // check if it's the valid command
  char *sample[8] = { "penup", "pendown", "colour", "forward",
  "backward", "right", "left" ,"loop"};

  for(int j = 0; j<8; j++){
    if(strcmp(cmd, sample[j]) == 0)
      return 1;
  }
  return 0;
}

CmdNode *newCmdNode(char cmd[10], int val) {
  /** 
   * This function allocates a new CmdNode struct and initializes it's values 
   * based on the input paramaters given. The next pointer is always 
   * initialized to NULL.
   * 
   * If the 'cmd' parameter is not a correct command, then print
   * "Invalid command.\n" and return NULL.
   * 
   * Note that we will always pass in a value here, even if the 
   * command doesn't need one. In this case, we can just ignore 
   * it. It saves us from having to make separate functions to 
   * deal with this.
   * 
   * TODO: Implement this function
   */
  if(!validCmd(cmd)){
    printf("Invalid command.\n");
    return NULL;
  }
  CmdNode *newNode = (CmdNode *)calloc(1, sizeof(CmdNode));
  if(newNode == NULL){
    return NULL;
  }
  strcpy(newNode->cmd, cmd);
  newNode->val = val;
  newNode->loop_head = NULL;
  newNode->next = NULL;
  return newNode;
}

/*---------------------------------------------------------------------------*/

int withValue(CmdNode *node){
  if(strcmp(node->cmd, "colour") == 0 || 
     strcmp(node->cmd, "forward") == 0 ||
     strcmp(node->cmd, "backward") == 0 ||
     strcmp(node->cmd, "loop") == 0)
      return 1;
  return 0;
}

void printCommand(CmdNode *node, int counter, char *space){
  if(withValue(node)){
      printf("%3d: %s%s %d\n", counter, space, node->cmd, node->val);
    }
  else{
    printf("%3d: %s%s\n", counter, space, node->cmd);
  }
  return;
}

void printCommandList(CmdNode *head) {
  /**
   * This function prints out each command in the linked list one after the 
   * other. Each command MUST also have a line number printed before it, this 
   * is what you will be using to modify / delete them. To do this, initialize 
   * a counter and then increment it for each command.
   * 
   * Depending on whether or not the command needs an additional value 
   * (like forward, backward and colour), use one of the following statements 
   * to print out the information for each node: 
   *            [ The format is "linenumber: command value" ]
   * 
   * printf("%3d: %s %d\n", ... );     [With a value]
   * 
   * printf("%3d: %s\n", ... );        [Without a value]
   * 
   * Obviously, you also need to pass in the correct parameters to the print 
   * function yourself, this is just so you have the correct format.
   * 
   * TODO: Implement this function
   */
  if(head == NULL)
    return;
  int counter = 0;
  while(head != NULL){
    printCommand(head, counter, "");
    counter++;
    if(strcmp(head->cmd, "loop") == 0){
      for (CmdNode *curr = head->loop_head; curr != NULL; curr=curr->next){
        printCommand(curr, counter, "  ");
        counter++;
      }
    }
    head = head->next;
  }
  return;
}

/*---------------------------------------------------------------------------*/

void queryByCommand(CmdNode *head, char cmd[10]) {
  /**
   * This function looks for commands in the linked list that match the input 
   * query. It prints them out in the same format as the printCommandList() 
   * function.
   * 
   * Make sure that the line number of the commands that match is the same as 
   * the line number that would be printed by the printCommandList() function.
   * 
   * --------------------------------------------------------------------------
   * 
   * For instance, if your printCommandList function outputs
   * 
   *    0: penup
   *    1: forward 200
   *    2: right
   *    3: forward 50
   * 
   * Then, if this function is called with the same list and cmd = "forward", 
   * then your output here should be
   * 
   *    1: forward 200
   *    3: forward 50
   * 
   * TODO: Implement this function
   */
  if(head == NULL)
    return;
  int counter = 0;
  while(head != NULL){
    if(strcmp(head->cmd, cmd) == 0){
      printCommand(head, counter, "");
    }
    counter++;
    if(strcmp(head->cmd, "loop") == 0){
      for (CmdNode *curr = head->loop_head; curr != NULL; curr=curr->next){
        if (strcmp(curr->cmd, cmd) == 0)
          printCommand(curr, counter, "");
        counter++;
      }
    }
    head = head->next;
  }
  return;
}

/*---------------------------------------------------------------------------*/

int countCommands(CmdNode *head) {
  /**
   * This function counts and returns the length of the linked list. It 
   * requires list traversal.
   * 
   * TODO: Implement this function
   */
  int counter = 0;
  if(head == NULL)
    return 0;
  while(head != NULL){
    if(strcmp(head->cmd, "loop") == 0){
      CmdNode *curr = head->loop_head;
      while(curr != NULL){
        counter++;
        curr = curr->next;
      }
    }
    counter++;
    head = head->next;
  }
  return counter;
}

/*---------------------------------------------------------------------------*/

CmdNode *insertCommand(CmdNode *head, CmdNode *new_CmdNode) {
  /**
   * This function inserts the node new_CmdNode *at the tail* of the linked 
   * list. (You are adding a command at the end).
   * 
   * If head == NULL, then the linked list is still empty.
   * 
   * It returns a pointer to the head of the linked list with the new node 
   * added into it.
   * 
   * TODO: Implement this function
   */
  if(head == NULL)
    return new_CmdNode;
  CmdNode *temp = head;
  while(temp->next != NULL){
    temp = temp->next;
  }
  temp->next = new_CmdNode;
  return head;
}

/*---------------------------------------------------------------------------*/

void insertCommandLoop(CmdNode *loopNode, CmdNode *new_CmdNode) {
  /*
  * insert a command to a CmdNode loop
  */
  if(loopNode == NULL || new_CmdNode == NULL)
    return;
  if (loopNode->loop_head == NULL){
    loopNode->loop_head = new_CmdNode;
    return;
  }
  
  CmdNode *curr = loopNode->loop_head;
  while(curr->next != NULL){
    curr = curr->next;
  }
  curr->next = new_CmdNode;
  new_CmdNode->next = NULL;
}


/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------*/


CmdNode *deleteCommandList(CmdNode *head) {
  /**
   * This function deletes the linked list of commands, releasing all the 
   * memory allocated to the nodes in the linked list.
   * 
   * Returns a NULL pointer so that the head of the list can be set to NULL
   * after deletion.
   * 
   * TODO: Implement this function
   */
  if(head == NULL)
    return NULL;
  while(head != NULL){
    CmdNode *temp = head->next;
    if (strcmp(head->cmd, "loop") == 0) {
    CmdNode *curr = head->loop_head;
    while (curr != NULL) {
      CmdNode *temp_loop = curr->next;
      free(curr);
      curr = temp_loop;
    }
  }
  free(head);
  head = temp;
  }
  return NULL;
}

/*---------------------------------------------------------------------------*/

void run(Image *im, CmdNode *head, int *endX, int *endY) {
  /**
   * This function runs the list of commands to move the turtle around and draw 
   * the image, and returns the final position of the turtle in the variables 
   * endX and endY.
   * 
   * --------------------------------------------------------------------------
   * 
   * NOTE: In the image we work with, the top-left pixel is (0,0),
   *       - x increases as you go right, up till SIZEX-1
   *       - y increases as you go down, up till SIZEY-1
   * 
   *                 (0,0)                 (SIZEX-1, 0)
   *                   x------------------------x
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |          IMAGE         |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   |                        |
   *                   x------------------------x
   *             (0, SIZEY-1)            (SIZEX-1, SIZEY-1)
   * 
   * The image is in grayscale (black and white), so the colours are numbers 
   * from [0-255] where 0 is black, 255 is white, and the values in between 
   * are varying levels of gray.
   * 
   * You need to understand how the (x,y) values are stored so you know how 
   * they should be updated when you move (down means y increases, etc). You do 
   * not need to use the 'im' variable for anything other than passing it into 
   * the drawLine() function described below.
   * 
   * --------------------------------------------------------------------------
   * 
   * Here's the setup - There is a turtle (with a pen) that walks along the 
   * image. When the pen is down (on the paper), it draws a line along the path 
   * that it walks on. (If you want to play around with this, consider looking 
   * at the `turtle` library in python!)
   * 
   * The turtle initially starts at pixel (0, 0) [at the top left], 
   * facing right (in the positive x direction). The pen starts off
   * as `down`, with the default colour being black (0).
   * 
   * You need to go through the linked list and 'run' the commands to keep 
   * track of the turtles position, and draw the appropriate lines. Here is 
   * what each command should do:
   * 
   *  - penup          : Put the pen up (stop drawing)
   *  - pendown        : Put the pen down (start / continue drawing)
   *  - colour <val>   : Draw lines in colour <val> from now on
   *  - forward <val>  : Move the turtle forward <val> steps (pixels) 
   *                     in the direction it is facing.
   *  - backward <val> : Same as above, except move backwards
   *  - right          : Turn the turtle to the right by 90 degrees
   *  - left           : Turn the turtle to the left by 90 degrees
   * 
   * NOTE: Make sure that you do *not* go outside the image. For this, set the 
   * maximum and minimum values of x and y to be 0 and SIZEX-1 / SIZEY-1 
   * respectively.
   * 
   * For instance, if the turtle is at (0,0) facing right, and your command is
   * `forward 100000`, it will only go forward till (SIZEX-1, 0), and end 
   * up at the rightmost pixel in that row.
   * 
   * IMPORTANT: Once you are done with all the commands, make sure you save the 
   * final (x,y) location of the turtle into the variables endX and endY.
   * 
   * --------------------------------------------------------------------------
   * 
   * We have already implemented a drawLine() function (in imgUtils.c) which 
   * you should use to actually draw the lines. It takes in the following:
   * 
   *      - a pointer to an image struct (use 'im')
   *      - (x,y) location of start point
   *      - (x,y) location of end point
   *      - a colour to draw the line in [0-255]
   *          
   * Note that this function only draws horizontal and vertical lines, so 
   * either the x values or the y values of both points must be the same. 
   * Both these points *must* also be within the image. 
   *          [ 0 <= x < SIZEX,  0 <= y < SIZEY ]
   * 
   * 
   * TODO: Implement this function
   */
  if (head == NULL)
    return;

  *endX = 0;
  *endY = 0;
  int pendown = 1;
  int currColour = 0;
  char currDirection[10] = "right";

  while (head != NULL) {
    int initial_x = *endX;
    int initial_y = *endY;

    if (strcmp(head->cmd, "penup") == 0)
      pendown = 0;
    else if (strcmp(head->cmd, "pendown") == 0)
      pendown = 1;
    else if (strcmp(head->cmd, "colour") == 0)
      currColour = head->val;
    else if (strcmp(head->cmd, "right") == 0) {
      if (strcmp(currDirection, "right") == 0) strcpy(currDirection, "down");
      else if (strcmp(currDirection, "down") == 0) strcpy(currDirection, "left");
      else if (strcmp(currDirection, "left") == 0) strcpy(currDirection, "up");
      else if (strcmp(currDirection, "up") == 0) strcpy(currDirection, "right");
    } else if (strcmp(head->cmd, "left") == 0) {
      if (strcmp(currDirection, "right") == 0) strcpy(currDirection, "up");
      else if (strcmp(currDirection, "up") == 0) strcpy(currDirection, "left");
      else if (strcmp(currDirection, "left") == 0) strcpy(currDirection, "down");
      else if (strcmp(currDirection, "down") == 0) strcpy(currDirection, "right");
    } else if (strcmp(head->cmd, "forward") == 0 || strcmp(head->cmd, "backward") == 0) {
      int dx = 0, dy = 0, move = head->val;
      if (strcmp(head->cmd, "backward") == 0)
        move = -move;

      if (strcmp(currDirection, "up") == 0) dy = -move;
      else if (strcmp(currDirection, "down") == 0) dy = move;
      else if (strcmp(currDirection, "right") == 0) dx = move;
      else if (strcmp(currDirection, "left") == 0) dx = -move;

      *endX += dx;
      *endY += dy;
      if (*endX < 0) *endX = 0;
      else if (*endX >= SIZEX) *endX = SIZEX - 1;
      if (*endY < 0) *endY = 0;
      else if (*endY >= SIZEY) *endY = SIZEY - 1;

      if (pendown)
        drawLine(im, initial_x, initial_y, *endX, *endY, currColour);
    }

    else if (strcmp(head->cmd, "loop") == 0) {
      int times = head->val;
      for (int i = 0; i < times; i++) {
        // 保存当前状态
        int subX = *endX;
        int subY = *endY;
        int subPen = pendown;
        int subColour = currColour;
        char subDir[10];
        strcpy(subDir, currDirection);

        CmdNode *curr = head->loop_head;
        while (curr != NULL) {
          int initial_x = subX;
          int initial_y = subY;

          if (strcmp(curr->cmd, "penup") == 0)
            subPen = 0;
          else if (strcmp(curr->cmd, "pendown") == 0)
            subPen = 1;
          else if (strcmp(curr->cmd, "colour") == 0)
            subColour = curr->val;
          else if (strcmp(curr->cmd, "right") == 0) {
            if (strcmp(subDir, "right") == 0) strcpy(subDir, "down");
            else if (strcmp(subDir, "down") == 0) strcpy(subDir, "left");
            else if (strcmp(subDir, "left") == 0) strcpy(subDir, "up");
            else if (strcmp(subDir, "up") == 0) strcpy(subDir, "right");
          } else if (strcmp(curr->cmd, "left") == 0) {
            if (strcmp(subDir, "right") == 0) strcpy(subDir, "up");
            else if (strcmp(subDir, "up") == 0) strcpy(subDir, "left");
            else if (strcmp(subDir, "left") == 0) strcpy(subDir, "down");
            else if (strcmp(subDir, "down") == 0) strcpy(subDir, "right");
          } else if (strcmp(curr->cmd, "forward") == 0 || strcmp(curr->cmd, "backward") == 0) {
            int dx = 0, dy = 0, move = curr->val;
            if (strcmp(curr->cmd, "backward") == 0) move = -move;

            if (strcmp(subDir, "up") == 0) dy = -move;
            else if (strcmp(subDir, "down") == 0) dy = move;
            else if (strcmp(subDir, "right") == 0) dx = move;
            else if (strcmp(subDir, "left") == 0) dx = -move;

            subX += dx;
            subY += dy;

            if (subX < 0) subX = 0;
            else if (subX >= SIZEX) subX = SIZEX - 1;
            if (subY < 0) subY = 0;
            else if (subY >= SIZEY) subY = SIZEY - 1;

            if (subPen)
              drawLine(im, initial_x, initial_y, subX, subY, subColour);
          }

          curr = curr->next;
        }

        // 更新主状态
        *endX = subX;
        *endY = subY;
        pendown = subPen;
        currColour = subColour;
        strcpy(currDirection, subDir);
      }
    }

    head = head->next;
  }
}


/*---------------------------------------------------------------------------*/
// All done!