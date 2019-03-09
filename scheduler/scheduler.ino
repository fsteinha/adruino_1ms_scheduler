/*
 ******************************************************
 * \brief Simple scheduler for adruino ide
 ******************************************************
 */


/*
 ******************************************************
 * typedefs
 ******************************************************
 */

/* struct for scheduler tab */
typedef struct
{
  /* falg task is execute (cyclic) */
  bool b_execute;
  /* task index where the task should execute */
  unsigned int ui_task_idx;
  /* pointer to scheduler function */  
  void (*scheduler_func)(void);
}T_SchedulerTab;

/*
 ******************************************************
 * Prototypes for scheduler functions
 ******************************************************
 */
 
/* example blink (toogle led withc echa call)*/ 
void blink_task();
/* example led on to each task time */ 
void led_on();
/* example led off to each task time */ 
void led_off();

/*
 ******************************************************
 * Globals
 ******************************************************
 */

/* 
 *  Scheduler table.
 *  Index muss arrange in ascending order
 */
T_SchedulerTab m_s_scheduler_tab_static[]=
{
  /* Task at 100 ms */
  { false, 100, led_on },
  /* Task at 200 ms */
  { false, 500, led_off},
};

T_SchedulerTab m_s_scheduler_tab_cyclic[]=
{
  /* Task at every 500 ms */
  { false, 500, NULL}
};

/* previous ms value */
static int m_i_prev_cnt_ms = 0;
/* ms counter for compare the next task index */
static int m_i_scheduler_task_cnt_ms = 0;                       
/* task counter in static scheduler table */
static int m_i_scheduler_task_cnt_static = 0;
/* sizeof static scheduler table */
static int m_i_scheduler_size_static = sizeof(m_s_scheduler_tab_static)/sizeof(*m_s_scheduler_tab_static);
/* task counter in static scheduler table */
static int m_i_scheduler_task_cnt_cyclic = 0;
/* sizeof cyclic scheduler table */
static int m_i_scheduler_size_cyclic = sizeof(m_s_scheduler_tab_cyclic)/sizeof(*m_s_scheduler_tab_cyclic);


/* 
 ******************************************************
 * Functions
 ******************************************************
 */

/* Arduino global init */
void setup()
{ 
  /* init mill counter */
  m_i_prev_cnt_ms = millis();               
}

/* Arduino program loop */
void loop()
{
  int i_cnt_ms = millis();

  if ((i_cnt_ms - m_i_prev_cnt_ms) >= 1)
  {
    m_i_scheduler_task_cnt_ms++;

    /* Static part */
    if (m_i_scheduler_task_cnt_static >= (m_i_scheduler_size_static))
    {     
      m_i_scheduler_task_cnt_static = 0;
      m_i_scheduler_task_cnt_ms = 1;
    }
    
    if (m_i_scheduler_task_cnt_ms == m_s_scheduler_tab_static[m_i_scheduler_task_cnt_static].ui_task_idx)
    {
      m_s_scheduler_tab_static[m_i_scheduler_task_cnt_static].scheduler_func();
      m_i_scheduler_task_cnt_static++;
    }

    /* cyclic part */
    if (m_i_scheduler_task_cnt_cyclic >= (m_i_scheduler_size_cyclic))
    {
      m_i_scheduler_task_cnt_cyclic = 0;
    }

    if ((m_s_scheduler_tab_cyclic[m_i_scheduler_task_cnt_cyclic].scheduler_func != NULL) &&
        (m_s_scheduler_tab_cyclic[m_i_scheduler_task_cnt_cyclic].b_execute  == false) && 
        ((m_s_scheduler_tab_cyclic[m_i_scheduler_task_cnt_cyclic].ui_task_idx & m_i_scheduler_task_cnt_ms) > 0))
    {
      m_s_scheduler_tab_cyclic[m_i_scheduler_task_cnt_cyclic].scheduler_func();
      m_s_scheduler_tab_cyclic[m_i_scheduler_task_cnt_cyclic].b_execute = true;
      m_i_scheduler_task_cnt_cyclic++;
    }
    else if ((m_s_scheduler_tab_cyclic[m_i_scheduler_task_cnt_cyclic].ui_task_idx & m_i_scheduler_task_cnt_ms) == 0)
    {
      m_s_scheduler_tab_cyclic[m_i_scheduler_task_cnt_cyclic].b_execute = false;
    }

    m_i_prev_cnt_ms = i_cnt_ms;
  }
}
