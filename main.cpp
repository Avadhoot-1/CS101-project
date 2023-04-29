#include <simplecpp>
#include "shooter.h"
#include "bubble.h"


/* Simulation Vars */
const double STEP_TIME = 0.02;

/* Game Vars */
const int PLAY_Y_HEIGHT = 450;
const int LEFT_MARGIN = 70;
const int TOP_MARGIN = 20;
const int BOTTOM_MARGIN = (PLAY_Y_HEIGHT + TOP_MARGIN);
const int UPPER_BORDER = 50 ;                                       /// UPPER BORDER ADDED


void move_bullets(vector<Bullet> &bullets){
    /// move all bullets
    for(unsigned int i=0; i<bullets.size(); i++){                   /// if bullet goes out of canvas -> erase it.
        if(!bullets[i].nextStep(STEP_TIME)){
            bullets.erase(bullets.begin()+i);
        }
    }
}

void move_bubbles(vector<Bubble> &bubbles ,int level){
    /// move all bubbles
    for (unsigned int i=0; i < bubbles.size(); i++)
    {
        bubbles[i].nextStep(STEP_TIME , level *4);                    /// gravity = level * 4
    }
}



vector<Bubble> create_bubbles (int level)
{
    /// create initial bubbles in the game
    vector<Bubble> bubbles;

    if(level == 1){
        bubbles.push_back(Bubble(WINDOW_X/2.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS , -BUBBLE_DEFAULT_VX, 0, COLOR(255,105,180)));
        bubbles.push_back(Bubble(WINDOW_X/4.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS  , BUBBLE_DEFAULT_VX, 0, COLOR(255,105,180)));
    }
    if(level == 2){
        bubbles.push_back(Bubble(WINDOW_X/2.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS *2 , -BUBBLE_DEFAULT_VX , 0, COLOR(155,25,255)));
        bubbles.push_back(Bubble(WINDOW_X/4.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS *2 , BUBBLE_DEFAULT_VX , 15, COLOR(155,25,255)));
        bubbles.push_back(Bubble(WINDOW_X/3.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS *2 , BUBBLE_DEFAULT_VX + 15, 0, COLOR(155,25,255)));
    }
    if(level == 3){
        bubbles.push_back(Bubble(WINDOW_X/2.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS *4 , -BUBBLE_DEFAULT_VX, 0, COLOR(21,149,253)));
        bubbles.push_back(Bubble(WINDOW_X/4.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS *4 , BUBBLE_DEFAULT_VX, 25, COLOR(21,149,253)));
        bubbles.push_back(Bubble(WINDOW_X/3.0, BUBBLE_START_Y, BUBBLE_DEFAULT_RADIUS *4 , BUBBLE_DEFAULT_VX + 25 , 0, COLOR(21,149,253)));

    }

    return bubbles;
}




void shot_successful ( vector<Bubble> &bubbles ,vector <Bullet> &bullets,int &score ,int level ){
     for (unsigned int i=0; i < bubbles.size(); i++){
        for (unsigned int j=0; j < bullets.size(); j++){
            double r = bubbles[i].get_radius();
            double h = bullets[j].get_height();
            double w = bullets[j].get_width();
            double absissa = bullets[j].get_center_x();
            double ordinate = bullets[j].get_center_y();
            double centrex = bubbles[i].get_center_x();
            double centrey = bubbles[i].get_center_y();


            if ((absissa <= centrex + r +w/2 && absissa >= centrex - r - w/2)
                &&
                (ordinate <= centrey + r + h/2 && ordinate >= centrey - r -h/2 )){       /// bullet hits bubble
                bubbles.erase(bubbles.begin() + i );
                bullets.erase(bullets.begin() + j );
                score ++;                                                                /// SCORE INCREASED

                if(r == BUBBLE_DEFAULT_RADIUS * 2 && level == 2 ){
                    /// two bubbles centered at the centre of destroyed bubble
                    bubbles.push_back(Bubble(centrex,centrey , BUBBLE_DEFAULT_RADIUS , BUBBLE_DEFAULT_VX , 50, COLOR(155,25,255)));
                    bubbles.push_back(Bubble(centrex,centrey , BUBBLE_DEFAULT_RADIUS , -BUBBLE_DEFAULT_VX , 50, COLOR(155,25,255)));

                }
                if(r == BUBBLE_DEFAULT_RADIUS * 2 && level ==3){
                    bubbles.push_back(Bubble(centrex,centrey , BUBBLE_DEFAULT_RADIUS , BUBBLE_DEFAULT_VX , 50, COLOR(21,149,253)));
                    bubbles.push_back(Bubble(centrex,centrey , BUBBLE_DEFAULT_RADIUS , -BUBBLE_DEFAULT_VX , 50, COLOR(21,149,253)));
                }
                if(r == BUBBLE_DEFAULT_RADIUS * 4 && level ==3){
                    bubbles.push_back(Bubble(centrex,centrey , BUBBLE_DEFAULT_RADIUS *2 , BUBBLE_DEFAULT_VX , 50, COLOR(21,149,253)));
                    bubbles.push_back(Bubble(centrex,centrey , BUBBLE_DEFAULT_RADIUS *2,  -BUBBLE_DEFAULT_VX , 50, COLOR(21,149,253)));
                }

            }

        }

    }

}



void  shooter_hit (vector<Bubble> &bubbles , int &health ,Shooter &shooter ,int &level,vector<Bullet> &bullets){
    for (unsigned int i=0; i < bubbles.size(); i++){
        double x = bubbles[i].get_center_x();
        double y = bubbles[i].get_center_y();
        double r = bubbles[i].get_radius();
        double head_x = shooter.get_head_center_x();
        double head_y = shooter.get_head_center_y();
        double head_r = shooter.get_head_radius();
        double body_x = shooter.get_body_center_x();
        double body_y = shooter.get_body_center_y();
        double body_w = shooter.get_body_width();
        double body_h = shooter.get_body_height();

        if((x >= head_x - r - head_r  && x <= head_x + r + head_r && y >= head_y - r - head_r && y <= head_y + r + head_r )
           ||
           (x >= body_x - r - body_w/2 && x <= body_x + r + body_w/2 && y >= body_y - r - body_h/2 && y <= body_y + r + body_h/2 )){

            ///if bubble hits shooter -> reduce health ;

            health --;
        }

        while((x >= head_x - r - head_r  && x <= head_x + r + head_r && y >= head_y - r - head_r && y <= head_y + r + head_r )
              ||
              (x >= body_x - r - body_w/2 && x <= body_x + r + body_w/2 && y >= body_y - r - body_h/2 && y <= body_y + r + body_h/2 )){

            /// while bubble is in contact of shooter ;  shooter turns red !!

            Shooter DUMMY (body_x , body_y , 0 , 30 , 18 , 8 , COLOR(255,0,0));
            move_bubbles(bubbles,level);
            move_bullets(bullets) ;
            x = bubbles[i].get_center_x();
            y = bubbles[i].get_center_y();
       }

   }

}




int main()
{
    int level= 1;
    initCanvas("Bubble Trouble", WINDOW_X, WINDOW_Y);
    int score =0;

    while(level <=3 ){

        int time = 1;
        int count = 0;
        int health = 5 ;

        {
        Text Level(WINDOW_X / 2,WINDOW_Y /2,("===================== LEVEL     ====================="));      ///for initial greetings
        Text level_count (270,WINDOW_Y / 2 ,level );
        Level.setColor(COLOR (0,0,255));
        level_count.setColor(COLOR (0,0,255));
        wait(2);
        }

        Text level_word (WINDOW_X / 2 , UPPER_BORDER / 2 ,"LEVEL :" );                                       /// SHOWS LEVEL
        level_word.setColor(COLOR(91,0, 46));
        level_word.imprint();
        Text level_number (WINDOW_X / 2 + textWidth("LEVEL :")/2 + 10 ,UPPER_BORDER / 2 , level);
        level_number.setColor(COLOR(91,0,46));
        level_number.imprint();

        Line border_1(0, PLAY_Y_HEIGHT, WINDOW_X, PLAY_Y_HEIGHT);                                            ///BOTTOM BORDER
        border_1.setColor(COLOR(0, 0, 255));

        Line border_2 (0,50 ,WINDOW_X,50);                                                                    ///TOP BORDER
        border_2.setColor(COLOR(0,0,255));

        Text Time_word (LEFT_MARGIN,TOP_MARGIN,("TIME : ")) ;
        Time_word.setColor(COLOR (252,3,78));
        Time_word.imprint();

        Text max_time (LEFT_MARGIN + textWidth ("TIME : ")/2 + 40 , TOP_MARGIN , " /  50 ");
        max_time.imprint();

        Text health_word (WINDOW_X - 70 , TOP_MARGIN , ("HEALTH : "));
        health_word.setColor(COLOR(113,0,225));
        health_word.imprint();

        Text score_word (WINDOW_X - 70 , PLAY_Y_HEIGHT + 20 ,("SCORE : "));
        score_word.setColor(COLOR(255,38,239));
        score_word.imprint();

        string msg_cmd("Cmd: _");
        Text charPressed(LEFT_MARGIN, BOTTOM_MARGIN, msg_cmd);

        /// Intialize the shooter
        Shooter shooter(SHOOTER_START_X, SHOOTER_START_Y, SHOOTER_VX);

        /// Initialize the bubbles
        vector<Bubble> bubbles = create_bubbles(level);

        /// Initialize the bullets (empty)
        vector<Bullet> bullets;

        XEvent event;

        /// Main game loop


        while (health != 0)
        {
            bool pendingEvent = checkEvent(event);
            if (pendingEvent)
            {
                /// Get the key pressed
                char c = charFromEvent(event);
                msg_cmd[msg_cmd.length() - 1] = c;
                charPressed.setMessage(msg_cmd);

                /// Update the shooter


                if(c == 'a')
                    shooter.move(STEP_TIME, true);
                else if(c == 'd')
                    shooter.move(STEP_TIME, false);
                else if(c == 'w'){
                    bullets.push_back(shooter.shoot());
                }
                else if(c == 'q')
                    return 0;
            }


            /// Update the bubbles
            move_bubbles(bubbles , level);

            /// Update the bullets
            move_bullets(bullets);



            shot_successful (bubbles,bullets,score,level);                                              /// ERASE BUBBLE AND BULLETS (IF COLLISION TAKES PLACE)


            shooter_hit(bubbles,health,shooter,level,bullets);                                          /// REDUCE HEALTH ON HITTING SHOOTER.


            count ++;
            if(count % 30 == 0 )                                                                        /// after 30 iterations -> 1 second
                time ++ ;

            Text health_count(WINDOW_X - 70 + (textWidth("HEALTH : "))/2 + 10 , TOP_MARGIN , health );
            health_count.imprint();                                                                     /// SHOWS HEALTH

            Text  Time_count (LEFT_MARGIN + textWidth ("TIME : ")/2 + 10 , TOP_MARGIN , time);
            Time_count.imprint();                                                                       ///SHOWS TIME

            Text scores(WINDOW_X - 70 + textWidth("SCORE : ") / 2 + 10 ,470,score);
            scores.imprint();                                                                           /// SHOWS SCORE

            if(time >= 50 || health <= 0 ){                                                             /// out of time or health !! OUT !!
                Text loss(250,250,(" *** GAME OVER *** "));
                loss.setColor(COLOR(255,0,0));
                loss.imprint();
                health = 0;
                wait(10);
                level = 100;                                                                            /// level = 100 ends both loops
            }


            if(bubbles.size()==0){                                                                      /// level inc on destroying all the bubbles
                Text congrats(250,250,("*** CONGRATULATIONS ***"));
                congrats.setColor(COLOR(0,255,0));
                wait (1);
                health = 0;                                                                             ///make health = 0 .. so as to terminate loop of current level


                Rectangle cover_time (LEFT_MARGIN + textWidth ("TIME : ")/2 + 10 , TOP_MARGIN ,15 ,10);
                cover_time.setColor(COLOR("white"));
                cover_time.setFill(true);
                cover_time.imprint();                                                                   /// white coloured rectangle hides previous imprinted time();
                time = 1;
                level ++;
            }

        }

          wait(STEP_TIME);
    }

    if(level == 4){
        Text won(250,250,"YOU WON !!!");
        Rectangle box (250,250,100,40);

        won.setColor(COLOR(84,31,243));
        won.imprint();
        box.imprint();
        repeat(4){
            box.scale(1.2);
            box.imprint();
        }

        wait(5);

    }
  }



