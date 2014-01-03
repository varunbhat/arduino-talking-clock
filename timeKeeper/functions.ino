char * getDateString(){
  snprintf(displayBuffer,MAX_LCD_STRING_LEN,"Date:%d/%d/%d\n",day(),month(),year());
  return displayBuffer;
}

char * getTimeString(){
  snprintf(displayBuffer,MAX_LCD_STRING_LEN,"%d:%d%d:%d%d %s\n",hour()%12,minute()/10,minute()%10,second()/10,second()%10,(hour()/12)?"PM":"AM");
  return displayBuffer;
}

