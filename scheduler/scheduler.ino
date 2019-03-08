/*
 * typedefs
 */

/* struct for scheduler tab */
typedef struct
{
  /* task index where the task should execute */
  unsigned int ui_task_idx;
  /* pointer to scheduler function */  
  void (*scheduler_func)(void);
}T_SchedulerTab;

/*
 * Prototypes for scheduler functions
 */
 
/* example blink (toogle led withc echa call)*/ 
void blink_task();
/* led on to each task time */ 
void led_on();
/* led off to each task time */ 
void led_off();

/*
 * Globals
 */

/* 
 *  Scheduler table.
 *  Index muss arrange in ascending order
 */
T_SchedulerTab m_s_scheduler_tab[]=
{
  { 500, led_on},   
  { 1000, led_off},   
};

/* previous ms value */
int m_i_prev_cnt_ms = 0;
/* ms counter for compare the next task index */
int m_i_scheduler_task_cnt_ms = 0;                       
/* task counter in scheduler table */
int m_i_scheduler_task_cnt = 0;


/* 
 * Functions
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
  int i_Cnt_ms = millis();

  if ((i_Cnt_ms - m_i_prev_cnt_ms) >= 1)
  {
    m_i_scheduler_task_cnt_ms++;

    if (m_i_scheduler_task_cnt >= sizeof(m_s_scheduler_tab)/sizeof(*m_s_scheduler_tab))
    {
      m_i_scheduler_task_cnt = 0;
      m_i_scheduler_task_cnt_ms = 0;
    }
    
    if (m_i_scheduler_task_cnt_ms == m_s_scheduler_tab[m_i_scheduler_task_cnt].ui_task_idx)
    {
      m_s_scheduler_tab[m_i_scheduler_task_cnt].scheduler_func();
      m_i_scheduler_task_cnt++;
    }

    m_i_prev_cnt_ms = i_Cnt_ms;
  }
}
