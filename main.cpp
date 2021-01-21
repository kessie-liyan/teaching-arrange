#include<cstdio>  
#include<iostream>  
#include<cstdlib>  
#include<algorithm>  
#include<stack>  
#include<queue>  
#include<cstring>  
  
using namespace std;  
  
///存放拓扑排序的结果  
typedef struct tuo_result  
{  
    int course_index;///课程号在字符串数组中的下标  
    int score;///课程的学分  
} tuo_result;  
typedef struct tuo_list  //拓扑排序得到的课程梯度  
{  
    tuo_result s[100];  
    int cnt;  
} tuo_list;  
  
char course_id[100][5]; ///课程号  
int score[100];  ///课程学分，下标与课程号的行下标对应  
int G[100][100]; ///课程之间的邻接矩阵  
int term; ///学期数  
int credit;///每学期学分上限  
int course_sum;///专业课程总数  
  
void prf_tidu(tuo_list *tidu, int tidu_sum);  
void prf_course_fen(int course_fen[][15], int term1);  
  
int judge_course_id_index(char *str); ///判断课程号的下标  
int scaf(int *temp); ///输入  
void add_e(int *temp);///添加先修关系  
void crtl_z_e(int *temp);///取消先修关系  
void temp_copy(int *temp, int *copy_tp);///做一份 每个课程的直接前驱数量数组  的副本  
int tuopu_sort(tuo_list *tidu, int &tidu_sum, int *temp);   ///拓扑排序，并且将分好梯度  
void tidu_copy(tuo_list *tidu, int tidu_sum, tuo_list *copy_t, int copy_sum); ///做一份梯度的副本  
int course_plan_xijie(tuo_list *tidu, int tidu_cnt, int *c, int &course_cnt, int term_cnt); ///排课细节  
int course_plan1(tuo_list *tidu, int tidu_sum, int course_fen[][15]); ///集中式排课  
int course_plan2(tuo_list *tidu, int tidu_sum, int course_fen[][15]); ///平均式排课  
void prf_file(int course_fen[][15], int times); ///写文件操作  
///删除课程号对应课程信息  
void dele_course(int &course_sum, int G[][100], int *score, char course_id[][5], int *temp);  
int dele_course_f(int &course_sum, int G[][100], int *score, char course_id[][5], char *name, int *temp);  
///添加课程和学分  
void add_course(int &course_sum, int G[][100], int *score, char course_id[][5]);  
  
  
int main()  
{  
    while(true)  
    {  
        printf("****************************是否输入课程信息？***************************************\n");  
        printf("****************************1: Yes!我要重新输入课程信息。****************************\n");  
        printf("****************************2: No!我要退出。*****************************************\n");  
        printf("请输入选项：\n");  
  
        int x;  
        scanf("%d", &x);  
        if(x == 1)  
        {  
  
            ///输入：  
            int temp[100];  ///输入课程关系时记录每门课的直接前驱数  
  
  
            memset(temp, 0, sizeof temp);  
            scaf(temp);  
  
  
            while(true)  
            {  
                printf("******************1):添加先修关系。****************************\n");  
                printf("******************2):取消一些先修关系。************************\n");  
                printf("******************3):将课程集中到前几个学期进行安排。**********\n");  
                printf("******************4):将课程平均分不到所有学期进行安排。********\n");  
                printf("******************5):添加新的课程。****************************\n");  
                printf("******************6):删除课程。********************************\n");  
                printf("******************7):退回上一级********************************\n");  
                printf("请输入选项(序号即可)：\n");  
                int xx;  
                scanf("%d", &xx);  
  
                if(xx == 1)  
                    add_e(temp);  
                else if(xx == 2)  
                    crtl_z_e(temp);  
                else if(xx == 3)  
                {  
                    ///拓扑排序  
                    int copy_temp[100];  
                    temp_copy(temp, copy_temp);  
                    tuo_list tidu[15];  
                    int tidu_sum;  
                    int re = tuopu_sort(tidu, tidu_sum, copy_temp);  
                    if(re)  
                    {  
                        printf("请重新输入\n");  
                        ///continue;  
                    }  
  
                    ///学习任务集中到前几个学期  
                    tuo_list tidu1[15];  
                    int tidu_sum1;  
                    tidu_copy(tidu, tidu_sum, tidu1, tidu_sum1); ///做一份梯度的副本  
  
                    int course_fen1[15][15]; ///每学期的课程安排，一行代表一学期  
                    if( course_plan1(tidu1, tidu_sum1, course_fen1) )  
                    {  
                        printf("请重新输入\n");  
                        continue;  
                    }  
                    ///输出排好的课程  
                    prf_course_fen(course_fen1, term);  
  
                    printf("是否将结果写到文件中？\n");  
                    printf("********1、Yes********\n");  
                    printf("********2、No*********\n");  
                    printf("请输入选项：\n");  
                    int xxx;  
                    scanf("%d", &xxx);  
                    if(xxx == 1)  
                        prf_file(course_fen1, 1);  
                }  
                else if(xx == 4)  
                {  
                    ///拓扑排序  
                    int copy_temp[100];  
                    temp_copy(temp, copy_temp);  
                    tuo_list tidu[15];  
                    int tidu_sum;  
                    int re = tuopu_sort(tidu, tidu_sum, copy_temp);  
                    if(re)  
                    {  
                        printf("请重新输入\n");  
                        continue;  
                    }  
  
                    ///学习任务平均分布每个学期  
                    tuo_list tidu2[15];  
                    int tidu_sum2;  
                    tidu_copy(tidu, tidu_sum, tidu2, tidu_sum2); ///做一份梯度的副本  
  
                    int course_fen2[15][15];///每学期的课程安排，一行代表一学期  
                    if( course_plan2(tidu2, tidu_sum2, course_fen2) )  
                    {  
                        printf("请重新输入\n");  
                        continue;  
                    }  
                    ///输出排好的课程  
                    prf_course_fen(course_fen2, term);  
  
                    printf("是否将结果写到文件中？\n");  
                    printf("********1、Yes********\n");  
                    printf("********2、No*********\n");  
                    printf("请输入选项：\n");  
                    int xxx;  
                    scanf("%d", &xxx);  
                    if(xxx == 1)  
                        prf_file(course_fen2, 0);  
                }  
                else if(xx == 5){  
                    add_course(course_sum, G, score, course_id);  
                }  
                else if(xx == 6){  
                    dele_course( course_sum, G, score, course_id, temp);  
                }  
                else if(xx == 7)  
                    break;  
                else  
                    printf("输入有误，请重新输入。\n");  
            }  
        }  
        else if(x == 2)  
        {  
            printf("再见！欢迎下次使用！\n");  
            break;  
        }  
        else  
                printf("输入有误，请重新输入。\n");  
    }  
    return 0;  
}  
  
///删除课程号对应课程信息  
void dele_course(int &course_sum, int G[][100], int *score, char course_id[][5], int *temp){  
    printf("请输入要删除的课程数目：\n");  
    int n;  
    scanf("%d", &n);  
  
    char name[100];  
    for(int i = 0; i < n; i++){  
        printf("请输入要删除的第%d个课程号！\n", i+1);  
        scanf(" %s", name);  
        int re = dele_course_f(course_sum, G, score, course_id, name, temp);  
        if(re == 1){  
            printf("删除成功！\n");  
        }  
        else{  
            printf("删除失败！\n");  
        }  
    }  
}  
int dele_course_f(int &course_sum, int G[][100], int *score, char course_id[][5], char *name, int *temp){  
  
    char cour_temp[100][5];  
    int G_temp[100][100];  
  
    ///记录要删除的课程号下标  
    int numb = judge_course_id_index(name);  
    if(numb == -1){  
        printf("输入课程号没找到，请检查准确无误后重新输入！\n");  
        return 0;  
    }  
  
    ///将原先课程号序列做一个副本  
    for(int i = 0; i < course_sum; i++){  
        int temp_j=0;  
        for(int j=0; course_id[i][j] != '\0'; j++){  
            cour_temp[i][j] = course_id[i][j];  
            temp_j = j;  
        }  
        cour_temp[i][temp_j+1] = '\0';  
    }  
    ///生成新的课程号序列  
    for(int i=numb; i<course_sum-1; i++){  
        int temp_k=0;  
        for(int k=0; course_id[i+1][k]!='\0'; k++){  
            course_id[i][k] = course_id[i+1][k];  
            temp_k=k;  
        }  
        course_id[i][temp_k+1]='\0';  
    }  
  
    ///重新生成新的课程先修关系邻接表，写到G_temp中  
    for(int i=0; i<course_sum; i++){  
        temp[i]=0;  
    }  
    for(int i=0; i<course_sum; i++){  
        if(i == numb) continue;  
        for(int j=0; j<course_sum; j++){  
            if(j == numb)   continue;  
  
            if(G[i][j]){  
                int s1, s2;  
                s1 = judge_course_id_index(cour_temp[i]);  
                s2 = judge_course_id_index(cour_temp[j]);  
                G_temp[s1][s2] = 1;  
                temp[s2]++;  
            }  
  
        }  
    }  
    ///将新的课程先修关系邻接表写回G[][]中  
    for(int i=0; i<course_sum-1; i++){  
        for(int j=0; j<course_sum-1; j++){  
            G[i][j] = G_temp[i][j];  
        }  
    }  
  
    ///删除掉需要删除的课程号的学分  
    for(int i=numb; i < course_sum-1; i++){  
        score[i] = score[i+1];  
    }  
    course_sum--;  
    return 1;  
}  
  
///添加课程和学分  
void add_course(int &course_sum, int G[][100], int *score, char course_id[][5]){  
    printf("请输入要添加的课程数目：\n");  
    int n;  
    scanf("%d", &n);  
  
    char name[100];  
    int scor;  
    for(int i = 0; i < n; i++){  
        printf("请输入第%d个课程的名称和学分，格式为：name score\n", i+1);  
        scanf(" %s %d", name, &scor);  
        score[course_sum] = scor;  
        for(int k=0; name[k]!='\0'; k++){  
            course_id[course_sum][k]=name[k];  
        }  
        printf("添加成功！\n");  
    }  
    course_sum++;  
}  
  
void prf_file(int course_fen[][15], int flag)  
{  
    FILE *fp;  
    if( (fp = fopen("file.txt", "a")) == NULL)  
        printf("文件打开失败\n");  
    if(flag == 1)  
        fputs("平均分布", fp);  
    else  
        fputs("集中式", fp);  
    fputs("式课程安排:\n", fp);  
    for(int i = 0; i < term; i++)  
    {  
        char ch = i + 1 + '0';  
        fputc(ch, fp);  
        fputs("学期的课程：\n", fp);  
        for(int j = 0; course_fen[i][j] >= 0; j++)  
            fputs(course_id[course_fen[i][j]], fp);  
        fputc('\n', fp);  
    }  
    fputs("\n\n", fp);  
    fclose(fp);  
}  
  
void crtl_z_e(int *temp)  
{  
    printf("请输入要取消的先修关系的数量：\n");  
    int n;  
    char str1[5], str2[5];  
    scanf("%d", &n);  
    printf("请输入要取消的先修关系，取消s2 的先修课 s1 的先修关系，输入格式为：s1  s2\n");  
    printf("请输入：\n");  
    for(int i = 0; i < n; i++)  
    {  
        scanf(" %s %s", str1, str2);  
        int s1, s2;  
        s1 = judge_course_id_index(str1);  
        s2 = judge_course_id_index(str2);  
        if(!G[s1][s2])  
        {  
            printf("%s 和 %s 无先修关系，此次输入作废，请继续输入。\n", str1, str2);  
            continue;  
        }  
        else  
        {  
            G[s1][s2] = 0;  
            temp[s2]--;  
        }  
    }  
}  
void add_e(int *temp)  
{  
    printf("请输入要添加的先修关系的数量：\n");  
    int n;  
    char str1[5], str2[5];  
    scanf("%d", &n);  
    printf("请输入要添加的先修关系，添加s2 的先修课 s1 的先修关系，输入格式为：s1  s2\n");  
    printf("请输入：\n");  
    for(int i = 0; i < n; i++)  
    {  
        scanf(" %s %s", str1, str2);  
        int s1, s2;  
        s1 = judge_course_id_index(str1);  
        s2 = judge_course_id_index(str2);  
        if(G[s1][s2])  
        {  
            printf("%s 和 %s 已存在先修关系，此次输入作废，请继续输入。\n", str1, str2);  
            continue;  
        }  
        else  
        {  
            G[s1][s2] = 1;  
            temp[s2]++;  
        }  
    }  
}  
void temp_copy(int *temp, int *copy_tp)  
{  
    for(int i = 0; i < course_sum; i++)  
        copy_tp[i] = temp[i];  
}  
  
void tidu_copy(tuo_list *tidu, int tidu_sum, tuo_list *copy_t, int copy_sum)  
{  
    copy_sum = tidu_sum;  
    for(int i = 0; i < tidu_sum; i++)  
    {  
        copy_t[i].cnt = tidu[i].cnt;  
        for(int j = 0; j < tidu[i].cnt; j++)  
        {  
            copy_t[i].s[j].course_index = tidu[i].s[j].course_index;  
            copy_t[i].s[j].score = tidu[i].s[j].score;  
        }  
    }  
}  
  
int course_plan_xijie(tuo_list *tidu, int tidu_cnt, int *c, int &course_cnt, int term_cnt, int course_max)  
{  
    int course_num = 0;  
  
    int c_score = 0;///一学期所排课的总学分  
  
    int c_i = 0;  
    tuo_result *s = tidu[tidu_cnt].s;  
  
  
    int s_i = 0, i;  
    for(i = 0; i < tidu[tidu_cnt].cnt; i++)  
    {  
        if(c_score + s[i].score <= credit)  
        {  
            c[c_i++] = s[i].course_index;  
            c_score += s[i].score;  
  
            course_cnt++;  
            course_num++;  
        }  
        else  
        {  
            s[s_i].course_index = s[i].course_index;  
            s[s_i++].score = s[i].score;  
        }  
        if(course_num >= course_max || (course_sum - course_cnt) <= (term - term_cnt))  
        {  
            for(i++ ; i < tidu[tidu_cnt].cnt; i++)  
            {  
                s[s_i].course_index = s[i].course_index;  
                s[s_i++].score = s[i].score;  
            }  
            tidu[tidu_cnt].cnt = s_i;  
            return 1;  
        }  
    }  
    tidu[tidu_cnt].cnt = s_i;  
  
    for(int i = 1; i < tidu_cnt+2; i += 2)  
    {  
        s = tidu[i].s;  
        s_i = 0;  
        for(int j = 0; j < tidu[i].cnt; j++)  
        {  
            if(c_score + s[j].score <= credit)  
            {  
                c[c_i++] = s[j].course_index;  
                c_score += s[j].score;  
  
                course_cnt++;  
                course_num++;  
            }  
            else  
            {  
                s[s_i].course_index = s[j].course_index;  
                s[s_i++].score = s[j].score;  
            }  
            if(course_num >= course_max || (course_sum - course_cnt) <= (term - term_cnt))  
            {  
                for(j++ ; j < tidu[i].cnt; j++)  
                {  
                    s[s_i].course_index = s[j].course_index;  
                    s[s_i++].score = s[j].score;  
                }  
                tidu[i].cnt = s_i;  
                return 1;  
            }  
        }  
        tidu[i].cnt = s_i;  
    }  
  
    return 0;  
  
}  
  
int course_plan1(tuo_list *tidu, int tidu_sum, int course_fen[][15])  
{  
  
  
    if(course_sum < term)  
    {  
        printf("给出的课程数小于学期数，不合法\n");  
        return 1;  
    }  
  
    int i, j, k;  
    for(i = 0; i < 15; i++)///初始化每学期的课  
        for(j = 0; j < 15; j++)  
            course_fen[i][j] = -1;  
    int tidu_cnt = 0, course_cnt = 0;  ///前者记录排到了第几梯度， 后者记录共安排了多少课程  
    int flag = 0;  
    for(i = 0; i < term; i++)  
    {  
        if( course_plan_xijie(tidu, tidu_cnt, course_fen[i], course_cnt, i+1, credit) )  
        {  
            flag = 1;  
            if(tidu[tidu_cnt].cnt <= 0)  
                tidu_cnt += 2;  
            break;  
        }  
        if(tidu[tidu_cnt].cnt <= 0 && tidu_cnt < tidu_sum-2)  
            tidu_cnt += 2;  
    }  
  
    if(flag)  
    {  
        for(i++ ; i < term && tidu_cnt < tidu_sum; tidu_cnt += 2)  
        {  
            for(j = 0; j < tidu[tidu_cnt].cnt; j++)  
            {  
                course_fen[i++][0] = tidu[tidu_cnt].s[j].course_index;  
                course_cnt++;  
            }  
        }  
        for(j = 1; j < tidu_sum; j += 2)  
        {  
            for(k = 0; k < tidu[j].cnt; k++)  
            {  
                course_fen[i++][0] = tidu[j].s[k].course_index;  
                course_cnt++;  
            }  
        }  
    }  
    else if(course_cnt < course_sum)  
    {  
        printf("输入课程数过多或已达到每学期学分上限，课成无法排完。\n");  
        return 1;  
    }  
  
    return 0;  
}  
int course_plan2(tuo_list *tidu, int tidu_sum, int course_fen[][15])  
{  
  
  
    if(course_sum < term)  
    {  
        printf("给出的课程数小于学期数，不合法\n");  
        return 1;  
    }  
  
    int i, j;  
    for(i = 0; i < 15; i++)///初始化每学期的课  
        for(j = 0; j < 15; j++)  
            course_fen[i][j] = -1;  
    int tidu_cnt = 0, course_cnt = 0;  ///前者记录排到了第几梯度， 后者记录共安排了多少课程  
  
    int averge_c = course_sum / term;  
    for(i = 0; i < term; i++)  
    {  
        int x = averge_c;  
        if(i < (course_sum % term))    x = averge_c + 1;  
  
        course_plan_xijie(tidu, tidu_cnt, course_fen[i], course_cnt, i+1, x);  
  
        if(tidu[tidu_cnt].cnt <= 0 && tidu_cnt < tidu_sum - 2)  
            tidu_cnt += 2;  
    }  
  
  
    if(course_cnt < course_sum)  
    {  
        printf("输入课程数过多或已达到每学期学分上限，课成无法排完。\n");  
        return 1;  
    }  
  
    return 0;  
}  
  
  
void prf_tidu(tuo_list *tidu, int tidu_sum)  
{  
    printf("\n\n");  
    printf("梯度的总数为：%d\n", tidu_sum);  
    for(int i = 0; i < tidu_sum; i++)  
    {  
        printf("%d梯度中的课程：\n", i);  
        for(int j = 0; j < tidu[i].cnt; j++)  
            printf("%d ", tidu[i].s[j].course_index);  
        printf("\n");  
    }  
}  
void prf_course_fen(int course_fen[][15], int term1)  
{  
    int i, j;  
    for(i = 0; i < term1; i++)  
    {  
        printf("\n%d学期的课程：\n", i+1);  
        for(j = 0; course_fen[i][j] >= 0; j++)  
            printf("%s : %d\n", course_id[course_fen[i][j]], score[course_fen[i][j]]);  
        printf("\n");  
    }  
}  
  
  
int tuopu_sort(tuo_list *tidu, int &tidu_sum, int *temp)  
{  
    int c_sum = 0;///被排序的课程数，判断输入是否存在环  
  
    int i, j;  
    tidu_sum = 0;  
    while(true)  
    {  
        tidu[tidu_sum].cnt = 0;///两个课程梯度初始化  
        tidu[tidu_sum+1].cnt = 0;  
  
  
        ///如果拓扑排序已完成就  break;  
        int tt0[100], tt_i = 0, flag = 1;//tt_i  记录这一趟中直接前驱为0的课程下标  
        for(i = 0; i < course_sum; i++)  
            if(temp[i] == 0)  
            {  
                tt0[tt_i++] = i;  
                temp[i]--;  
                flag = 0;  
            }  
        if(flag)  break;  
  
        ///拓扑排序之  删除图中直接前驱为0的课程  
        for(i = 0; i < tt_i; i++)  
        {  
            int biao = 1, c = tt0[i];  
            for(j = 0; j < course_sum; j++)  
                if(G[c][j])  
                {  
                    biao = 0;///标记进入有影响的  
  
                    temp[j]--;///拓扑排序之 直接前驱-1  
                }  
            tidu[tidu_sum+biao].s[tidu[tidu_sum+biao].cnt].course_index = c;  
            tidu[tidu_sum+biao].s[tidu[tidu_sum+biao].cnt++].score = score[c];  
            c_sum++;  
        }  
        tidu_sum += 2;  
    }  
    if(c_sum != course_sum)  
    {  
        printf("输入存在环！\n");  
        return 1;  
    }  
    if(tidu_sum / 2 > term)  
    {  
        printf("输入不合法，先修关系链长度大于学期数。\n");  
        return 1;  
    }  
    return 0;  
}  
  
  
int judge_course_id_index(char *str)  
{  
    int i = -1;  
    for(i = 0; i < course_sum; i++)  
    {  
        if(strcmp(course_id[i], str) == 0)  
            break;  
    }  
    return i;  
}  
  
int scaf(int *temp)  
{  
    printf("请输入专业学期数：\n");  
    scanf("%d", &term);  
  
    printf("请输入每学期学分上限：\n");  
    scanf("%d", &credit);  
  
    printf("请输入专业课程总数：\n");  
    scanf("%d", &course_sum);  
  
    printf("依次输入%d门课的课程号（固定3位长度的字母与数字组合），以空格隔开：\n", course_sum);  
    for(int i = 0; i < course_sum; i++)  
        scanf(" %s", course_id[i]);  
  
    printf("请依次输入%d门课的学分：\n", course_sum);  
    for(int i = 0; i < course_sum; i++)  
    {  
        scanf("%d", &score[i]);  
        if(score[i] > credit)  
        {  
            printf("输入学分不合法\n");  
            return 1;  
        }  
    }  
  
    int m, s1 = 0, s2 = 0;  
    char str1[10], str2[10];  
    printf("请输入课程之间的关系数及关系，如果s1 是 s2 的直接先修课程，则输入格式为：s1 s2\n");  
    printf("请输入课程关系数：\n");  
    scanf("%d", &m);  
    printf("请输入课程关系：\n");  
    for(int i = 0; i < course_sum; i++)  
        for(int j = 0; j < course_sum; j++)  
            G[i][j] = 0;  
    for(int i = 0; i < m; i++)  
    {  
        scanf(" %s %s", str1, str2);  
        s1 = judge_course_id_index(str1);  
        s2 = judge_course_id_index(str2);  
        if(s1 == s2 || s1 == -1 || s2 == -1)  
            printf("输入错误，请重新输入。\n");  
        else if(G[s1][s2])  
            printf("重复输入，请重新输入。\n");  
        else  
        {  
            G[s1][s2] = 1;  
            temp[s2]++;  
        }  
    }  
    return 0;  
}  

