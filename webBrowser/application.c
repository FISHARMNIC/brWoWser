// gcc $(pkg-config --cflags gtk4) -o hello-world-gtk textBrowser/hello-world-gtk.c $(pkg-config --libs gtk4)

#include <gtk/gtk.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 100000 // max characters per row
#define MAX_LINE_NUMBER 100000 // max rows

#include "libs/request.c"
#include "libs/parser.c"

extern int curlInto(char *buffer, char *command);
extern char *readAfter(char *string, char *substr, int index);

GtkWidget *addressBar;
GtkWidget *htmlData;
GtkWidget *window;

GtkWidget *VerticalStack;

char *_intputBuffer;

static void
httpReq(GtkWidget *widget,
        gpointer data)
{

  // loads input into a string
  char *requestTo = (char *)gtk_entry_buffer_get_text(gtk_entry_get_buffer(GTK_ENTRY(addressBar)));
  char command[100] = "curl \"";
  strcat(command, requestTo);
  strcat(command, "\"");

  _intputBuffer = malloc(MAX_LINE_LENGTH * MAX_LINE_NUMBER);
  curlInto(_intputBuffer, command);
  char buffer[strlen(_intputBuffer)];
  strcpy(buffer, _intputBuffer);
  free(_intputBuffer);

  subSection(1, TITLE, "<title>", "</title>", buffer);
  subSection(1, BODY, "<body", "</body>", buffer);

  gtk_window_set_title(GTK_WINDOW(window), TITLE);

  char *PARAGRAPH[100];
  int NUMP = loadStyleBuffer(PARAGRAPH, BODY, "<p>", "</p>");

  char *HEADING1[100];
  int NUMH1 = loadStyleBuffer(HEADING1, buffer, "<h1>", "</h1>");

  char *HEADING2[100];
  int NUMH2 = loadStyleBuffer(HEADING2, buffer, "<h2>", "</h2>");

  char *HEADING3[100];
  int NUMH3 = loadStyleBuffer(HEADING3, buffer, "<h3>", "</h3>");

  char *HEADING4[100];
  int NUMH4 = loadStyleBuffer(HEADING4, buffer, "<h4>", "</h4>");

  char *HEADING5[100];
  int NUMH5 = loadStyleBuffer(HEADING5, buffer, "<h5>", "</h5>");

  char *HEADING6[100];
  int NUMH6 = loadStyleBuffer(HEADING6, buffer, "<h6>", "</h6>");

  // char *PARAGRAPH[100];
  // int NUMP = loadStyleBuffer(PARAGRAPH, buffer, "<", "</");

  char pl[1000];
  char *pageLayout = pl;
  int totalElements = getPageLayout(pageLayout, BODY);

  int P_COUNTER = 0;
  int H1_COUNTER = 0;
  int H2_COUNTER = 0;
  int H3_COUNTER = 0;
  int H4_COUNTER = 0;
  int H5_COUNTER = 0;
  int H6_COUNTER = 0;

  g_print("to be rendered: %i\n", totalElements);
  // for each paragraph, make a new text section
  for (int i = 0; i < totalElements; i++)
  {
    switch (pageLayout[i])
    {
    case '>':
    {
      // PARAGRAPH
      GtkWidget *txt = gtk_label_new(NULL);
      gtk_label_set_markup(GTK_LABEL(txt), g_markup_printf_escaped("<span size=\"medium\">\%s</span>", PARAGRAPH[P_COUNTER++]));
      gtk_label_set_use_markup(GTK_LABEL(txt), true);
      gtk_box_append(GTK_BOX(VerticalStack), txt);
      break;
    }
    case '1':
    {
      // HEADING 1
      GtkWidget *txt = gtk_label_new(NULL);
      gtk_label_set_markup(GTK_LABEL(txt), g_markup_printf_escaped("<span size=\"xx-large\">\%s</span>", HEADING1[H1_COUNTER++]));
      gtk_label_set_use_markup(GTK_LABEL(txt), true);
      gtk_box_append(GTK_BOX(VerticalStack), txt);
      break;
    }
    case '2':
    {
      GtkWidget *txt = gtk_label_new(NULL);
      gtk_label_set_markup(GTK_LABEL(txt), g_markup_printf_escaped("<span size=\"x-large\">\%s</span>", HEADING2[H2_COUNTER++]));
      gtk_label_set_use_markup(GTK_LABEL(txt), true);
      gtk_box_append(GTK_BOX(VerticalStack), txt);
      break;
    }
    case '3':
    {
      GtkWidget *txt = gtk_label_new(NULL);
      gtk_label_set_markup(GTK_LABEL(txt), g_markup_printf_escaped("<span size=\"large\">\%s</span>", HEADING3[H3_COUNTER++]));
      gtk_label_set_use_markup(GTK_LABEL(txt), true);
      gtk_box_append(GTK_BOX(VerticalStack), txt);
      break;
    }
    case '4':
    {
      GtkWidget *txt = gtk_label_new(NULL);
      gtk_label_set_markup(GTK_LABEL(txt), g_markup_printf_escaped("<span size=\"small\">\%s</span>", HEADING4[H4_COUNTER++]));
      gtk_label_set_use_markup(GTK_LABEL(txt), true);
      gtk_box_append(GTK_BOX(VerticalStack), txt);
      break;
    }
    case '5':
    {
      GtkWidget *txt = gtk_label_new(NULL);
      gtk_label_set_markup(GTK_LABEL(txt), g_markup_printf_escaped("<span size=\"x-small\">\%s</span>", HEADING5[H5_COUNTER++]));
      gtk_label_set_use_markup(GTK_LABEL(txt), true);
      gtk_box_append(GTK_BOX(VerticalStack), txt);
      break;
    }
    case '6':
    {
      GtkWidget *txt = gtk_label_new(NULL);
      gtk_label_set_markup(GTK_LABEL(txt), g_markup_printf_escaped("<span size=\"large\">\%s</span>", HEADING6[H6_COUNTER++]));
      gtk_label_set_use_markup(GTK_LABEL(txt), true);
      gtk_box_append(GTK_BOX(VerticalStack), txt);
      break;
    }
    }
  }

  // gtk_label_set_text (GTK_LABEL(htmlData),PARAGRAPH[0]);
}

// ----------- Main App -----------
static void
activate(GtkApplication *app,
         gpointer user_data)
{
  window = gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window), "BrWOWser");
  gtk_window_set_default_size(GTK_WINDOW(window), 500, 300);

  // vertical stack for top being the search bar + enter button
  VerticalStack = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
  GtkWidget *topRow = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 10);

  // search bar and enter button
  addressBar = gtk_entry_new();
  GtkWidget *addressButton = gtk_button_new_with_label("Enter");
  g_signal_connect(addressButton, "clicked", G_CALLBACK(httpReq), NULL);

  htmlData = gtk_label_new(NULL);

  // Top bar
  gtk_box_prepend(GTK_BOX(topRow), addressButton);
  gtk_box_prepend(GTK_BOX(topRow), addressBar);

  gtk_box_prepend(GTK_BOX(VerticalStack), htmlData);
  gtk_box_prepend(GTK_BOX(VerticalStack), topRow);

  gtk_window_set_child(GTK_WINDOW(window), VerticalStack);
  gtk_window_present(GTK_WINDOW(window));
  // gtk_widget_show (text);
}

int main(int argc,
         char **argv)
{

  GtkApplication *app;
  int status;

  app = gtk_application_new("org.nick.brwowser", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
  status = g_application_run(G_APPLICATION(app), argc, argv);
  g_object_unref(app);

  return status;
}