#include <stdio.h>
#include <gio/gio.h>
GMainLoop *loop;
const char *xml =
    "<node>"
    " <interface name='com.example.Notify'>"
    "  <method name='SendNotification'>"
    "   <arg type='s' direction='in'/>"
    "   <arg type='s' direction='out'/>"
    "  </method>"
    " </interface>"
    "</node>";
void method_call(GDBusConnection *conn,
                 const char *sender,
                 const char *path,
                 const char *interface,
                 const char *method,
                 GVariant *params,
                 GDBusMethodInvocation *invocation,
                 gpointer data)
{    const char *msg;
    g_variant_get(params, "(&s)", &msg);
    printf("알림 메시지: %s\n", msg);
    g_dbus_method_invocation_return_value(
        invocation, g_variant_new("(s)", "전송 완료"));
}void bus_acquired(GDBusConnection *conn,
                  const char *name,
                  gpointer data)
{    GError *error = NULL;
    GDBusNodeInfo *info = g_dbus_node_info_new_for_xml(xml, &error);
    if (info == NULL) {
        g_printerr("XML 오류: %s\n", error->message);
        g_clear_error(&error);
        g_main_loop_quit(loop);
        return;
    }
    GDBusInterfaceVTable table = { method_call, NULL, NULL };
    guint id = g_dbus_connection_register_object(
        conn,
        "/com/example/Notify",
        info->interfaces[0],
        &table,
        NULL, NULL, &error);
    if (id == 0) {
        g_printerr("등록 실패: %s\n", error->message);
        g_clear_error(&error);
        g_main_loop_quit(loop);
    }
    g_dbus_node_info_unref(info);
}void name_acquired(GDBusConnection *conn,
                   const char *name,
                   gpointer data)
{    printf("D-Bus 서버 실행 중...\n");
    printf("클라이언트 메시지 대기 중\n");
}void name_lost(GDBusConnection *conn,
               const char *name,
               gpointer data)
{    printf("D-Bus 서비스 연결 실패\n");
    g_main_loop_quit(loop);
}int main()
{    guint owner;
    loop = g_main_loop_new(NULL, FALSE);
    owner = g_bus_own_name(
        G_BUS_TYPE_SESSION,
        "com.example.NotifyService",
        G_BUS_NAME_OWNER_FLAGS_NONE,
        bus_acquired,
        name_acquired,
        name_lost,
        NULL, NULL);
    g_main_loop_run(loop);
    g_bus_unown_name(owner);
    g_main_loop_unref(loop);
    return 0;
}
