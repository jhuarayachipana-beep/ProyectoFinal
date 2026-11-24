#include <iostream>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <conio.h>
#include <windows.h>
#include <iomanip>
using namespace std;

/*
  CASO: SISTEMA DE GESTION HOSPITALARIA con struct y archivos de texto
  Separador de campos: |   (se puede cambiar en la constante SEP)

  pacientes.txt   : codigo|dni|nombre|edad|sexo|telefono|estado
  medicos.txt     : codigo|nombre|especialidad|consultorio|estado
  citas.txt       : codigo|codPaciente|codMedico|fecha|hora|estado
  atenciones.txt  : codCita|diagnostico|costo
  pagos.txt       : codCita|monto|estado
*/

const string ARCH_PACIENTES  = "C:/Users/ASUS/Desktop/C++/C++_Archivos/TF_Programacion/pacientes.txt";
const string ARCH_MEDICOS    = "C:/Users/ASUS/Desktop/C++/C++_Archivos/TF_Programacion/medicos.txt";
const string ARCH_CITAS      = "C:/Users/ASUS/Desktop/C++/C++_Archivos/TF_Programacion/citas.txt";
const string ARCH_ATENCIONES = "C:/Users/ASUS/Desktop/C++/C++_Archivos/TF_Programacion/atenciones.txt";
const string ARCH_PAGOS      = "C:/Users/ASUS/Desktop/C++/C++_Archivos/TF_Programacion/pagos.txt";
const string ARCHIVOS[5] = {ARCH_PACIENTES, ARCH_MEDICOS, ARCH_CITAS, ARCH_ATENCIONES, ARCH_PAGOS};

const string ESPECIALIDADES[5] = {
    "Medicina General", "Pediatria", "Cardiologia", "Traumatologia", "Dermatologia"
};

struct Paciente {
    string codigo;
    string dni;
    string nombre;
    int edad;
    char sexo;
    string telefono;
    string estado;      // Activo, Inactivo
};

struct Medico {
    string codigo;
    string nombre;
    string especialidad;
    string consultorio;
    string estado;
};

struct Cita {
    string codigo;
    string codPaciente;   // llave foranea -> Paciente.codigo
    string codMedico;     // llave foranea -> Medico.codigo
    string fecha;
    string hora;
    string estado;        // Programada, Atendida, Cancelada
};

struct Atencion {
    string codCita;       // llave foranea -> Cita.codigo
    string diagnostico;
    double costo;
};

struct Pago {
    string codCita;       // llave foranea -> Cita.codigo
    double monto;
    string estado;        // Pagado
};

void sistema();

int main(){
    SetConsoleOutputCP(CP_UTF8);
    sistema();
    return 0;
}

int menu(){
    int opcion;
    cout << "=== SISTEMA INTELIGENTE DE HOSPITAL ===" << endl;
    cout << "1. Registrar Paciente" << endl;
    cout << "2. Mostrar Pacientes" << endl;
    cout << "3. Registrar Médico" << endl;
    cout << "4. Mostrar Médicos" << endl;
    cout << "5. Registrar Cita" << endl;
    cout << "6. Registrar Atención" << endl;
    cout << "7. Registrar Pago" << endl;
    cout << "8. Consultas" << endl;
    cout << "9. Reportes" << endl;
    cout << "10. Guardar Datos" << endl;
    cout << "11. Cargar Datos" << endl;
    cout << "0. Salir" << endl;
    cout << "Seleccione: ";
    cin >> opcion;
    return opcion;
}

// ===============================================================
// LECTURA DE ARCHIVOS
// ===============================================================

bool leerPaciente(fstream &archivo, Paciente &p) {
    string sEdad, sSexo;
    if (!getline(archivo >> ws, p.codigo, '|')) return false;
    getline(archivo, p.dni,'|');
    getline(archivo, p.nombre,'|');
    getline(archivo, sEdad,'|');
    getline(archivo, sSexo,'|');
    getline(archivo, p.telefono, '|');
    getline(archivo, p.estado);
    p.edad = stoi(sEdad);
    p.sexo = sSexo[0];
    return true;
}

bool leerMedico(fstream &archivo, Medico &m) {
    if (!getline(archivo >> ws, m.codigo, '|')) return false;
    getline(archivo, m.nombre, '|');
    getline(archivo, m.especialidad, '|');
    getline(archivo, m.consultorio, '|');
    getline(archivo, m.estado);
    return true;
}

bool leerCita(fstream &archivo, Cita &c) {
    if (!getline(archivo >> ws, c.codigo, '|')) return false;
    getline(archivo, c.codPaciente, '|');
    getline(archivo, c.codMedico, '|');
    getline(archivo, c.fecha, '|');
    getline(archivo, c.hora, '|');
    getline(archivo, c.estado);
    return true;
}

bool leerAtencion(fstream &archivo, Atencion &a) {
    string sCosto;
    if (!getline(archivo >> ws, a.codCita, '|')) return false;
    getline(archivo, a.diagnostico, '|');
    getline(archivo, sCosto);
    a.costo = stod(sCosto);
    return true;
}

bool leerPago(fstream &archivo, Pago &p) {
    string sMonto;
    if (!getline(archivo >> ws, p.codCita, '|')) return false;
    getline(archivo, sMonto, '|');
    getline(archivo, p.estado);
    p.monto = stod(sMonto);
    return true;
}

// ===============================================================
// ESCRITURA DE ARCHIVOS
// ===============================================================

void escribirPaciente(fstream &archivo, Paciente p) {
    archivo << p.codigo << '|' << p.dni << '|' << p.nombre << '|' << p.edad << '|'
            << p.sexo << '|' << p.telefono << '|' << p.estado << "\n";
}

void escribirMedico(fstream &archivo, Medico m) {
    archivo << m.codigo << '|' << m.nombre << '|' << m.especialidad << '|'
            << m.consultorio << '|' << m.estado << "\n";
}

void escribirCita(fstream &archivo, Cita c) {
    archivo << c.codigo << '|' << c.codPaciente << '|' << c.codMedico << '|'
            << c.fecha << '|' << c.hora << '|' << c.estado << "\n";
}

void escribirAtencion(fstream &archivo, Atencion a) {
    archivo << a.codCita << '|' << a.diagnostico << '|' << a.costo << "\n";
}

void escribirPago(fstream &archivo, Pago p) {
    archivo << p.codCita << '|' << p.monto << '|' << p.estado << "\n";
}

// ===============================================================
// BUSQUEDAS (si no encuentran, devuelven el codigo vacio)
// ===============================================================

Paciente buscarPaciente(string codBuscado) {
    Paciente p;
    fstream archivo;
    archivo.open(ARCH_PACIENTES, ios::in);
    if(!archivo) {
        p.codigo = "";
        return p;
    }

    while (leerPaciente(archivo, p)) {
        if (p.codigo == codBuscado || p.dni == codBuscado) {
            archivo.close();
            return p;
        }
    }
    archivo.close();
    p.codigo = "";
    return p;
}

Medico buscarMedico(string codBuscado) {
    Medico m;
    fstream archivo;
    archivo.open(ARCH_MEDICOS, ios::in);
    if(!archivo) {
        m.codigo = "";
        return m;
    }
    
    while (leerMedico(archivo, m)) {
        if (m.codigo == codBuscado) {
            archivo.close();
            return m;
        }
    }
    archivo.close();
    m.codigo = "";
    return m;
}

Cita buscarCita(string codBuscado) {
    Cita c;
    fstream archivo;
    archivo.open(ARCH_CITAS, ios::in);
    if(!archivo) {
        c.codigo = "";
        return c;
    }
    
    while (leerCita(archivo, c)) {
        if (c.codigo == codBuscado) {
            archivo.close();
            return c;
        }
    }
    archivo.close();
    c.codigo = "";
    return c;
}

Atencion buscarAtencion(string codCita) {
    Atencion a;
    fstream archivo;
    archivo.open(ARCH_ATENCIONES, ios::in);
    if(!archivo) {
        a.codCita = "";
        return a;
    }
    
    while (leerAtencion(archivo, a)) {
        if (a.codCita == codCita) {
            archivo.close();
            return a;
        }
    }
    archivo.close();
    a.codCita = "";
    return a;
}

Pago buscarPago(string codCita) {
    Pago p;
    fstream archivo;
    archivo.open(ARCH_PAGOS, ios::in);
    if(!archivo) {
        p.codCita = "";
        return p;
    }
    
    while (leerPago(archivo, p)) {
        if (p.codCita == codCita) {
            archivo.close();
            return p;
        }
    }
    archivo.close();
    p.codCita = "";
    return p;
}

// Regla: un medico no puede tener dos citas programadas a la misma fecha y hora
bool horarioOcupado(string codMedico, string fecha, string hora) {
    fstream archivo;
    archivo.open(ARCH_CITAS, ios::in);
    if (!archivo) return false;

    Cita c;
    while (leerCita(archivo, c)) {
        if (c.codMedico == codMedico && c.fecha == fecha &&
            c.hora == hora && c.estado == "Programada") {
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}

// ===============================================================
// MOSTRAR
// ===============================================================

void listarPacientes() {
    fstream archivo;
    archivo.open(ARCH_PACIENTES, ios::in);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo de repartidores.\n";
        return;
    }
    Paciente p;

    cout << left << setw(8)  << "Codigo" << setw(10) << "DNI"
                 << setw(20) << "Nombre" << setw(6)  << "Edad"
                 << setw(6)  << "Sexo"   << setw(12) << "Telefono"
                 << setw(10) << "Estado" << "\n";
    cout << string(72, '-') << "\n";

    while(leerPaciente(archivo,p)) {
        cout << left << setw(8)  << p.codigo << setw(10) << p.dni
                     << setw(20) << p.nombre << setw(6)  << p.edad
                     << setw(6)  << p.sexo   << setw(12) << p.telefono
                     << setw(10) << p.estado << "\n";
    }
    archivo.close();
}

void listarMedicos() {
    fstream archivo;
    archivo.open(ARCH_MEDICOS, ios::in);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo de repartidores.\n";
        return;
    }
    Medico m;

    cout << left << setw(8)  << "Codigo" << setw(20) << "Nombre"
                 << setw(18) << "Especialidad" << setw(16) << "Consultorio"
                 << setw(10) << "Estado" << "\n";
    cout << string(72, '-') << "\n";

    while(leerMedico(archivo,m)) {
        cout << left << setw(8)  << m.codigo << setw(20) << m.nombre
                     << setw(18) << m.especialidad << setw(16) << m.consultorio
                     << setw(10) << m.estado << "\n";
    }
    archivo.close();
}

void listarCitas() {
    fstream archivo;
    archivo.open(ARCH_CITAS, ios::in);
    if (!archivo) {
        cerr << "No se pudo abrir el archivo de repartidores.\n";
        return;
    }

    Cita c;

    cout << left << setw(8)  << "Cita"  << setw(20) << "Paciente"
                 << setw(20) << "Medico" << setw(12) << "Fecha"
                 << setw(7)  << "Hora"  << setw(11) << "Estado" << "\n";
    cout << string(78, '-') << "\n";

    while(leerCita(archivo, c)) {
        string nomPac = buscarPaciente(c.codPaciente).nombre;
        string nomMed = buscarMedico(c.codMedico).nombre;
        cout << left << setw(8)  << c.codigo << setw(20) << nomPac
                     << setw(20) << nomMed   << setw(12) << c.fecha
                     << setw(7)  << c.hora   << setw(11) << c.estado << "\n";
    }
    archivo.close();
}

// ===============================================================
// REGISTROS
// ===============================================================

void registrarPaciente() {
    Paciente p;
    cout << "Codigo del paciente: ";
    getline(cin >> ws, p.codigo);
    if (buscarPaciente(p.codigo).codigo != "") {
        cout << "Error: ya existe un paciente con ese codigo.\n";
        return;
    }
    cout << "DNI: ";
    getline(cin >> ws, p.dni);
    cout << "Nombre completo: ";
    getline(cin >> ws, p.nombre);
    cout << "Edad: ";
    cin >> p.edad;
    cout << "Sexo (M/F): ";
    cin >> p.sexo;
    cout << "Telefono: ";
    getline(cin >> ws, p.telefono);
    p.estado = "Activo";

    fstream archivo;
    archivo.open(ARCH_PACIENTES, ios::out | ios::app);
    escribirPaciente(archivo, p);
    archivo.close();
    cout << "Paciente registrado!\n";
}

void registrarMedico() {
    Medico m;
    int opcion;
    cout << "Codigo del medico: ";
    getline(cin >> ws, m.codigo);
    if (buscarMedico(m.codigo).codigo != "") {
        cout << "Error: ya existe un medico con ese codigo.\n";
        return;
    }
    cout << "Nombre: ";
    getline(cin >> ws, m.nombre);
    cout << "Especialidades:\n";
    for (int i = 0; i < 5; i++)
        cout << i + 1 << ") " << ESPECIALIDADES[i] << endl;
    cout << "Elija la especialidad: ";
    cin >> opcion;
    if (opcion < 1 || opcion > 5) {
        cout << "Especialidad no valida. Registro cancelado.\n";
        return;
    }
    m.especialidad = ESPECIALIDADES[opcion - 1];
    cout << "Consultorio: ";
    getline(cin >> ws, m.consultorio);
    m.estado = "Activo";

    fstream archivo;
    archivo.open(ARCH_MEDICOS, ios::out | ios::app);
    escribirMedico(archivo, m);
    archivo.close();
    cout << "Medico registrado!\n";
}

void registrarCita() {
    Cita c;
    cout << "Codigo de la cita: ";
    getline(cin >> ws, c.codigo);
    if (buscarCita(c.codigo).codigo != "") {
        cout << "Error: ya existe una cita con ese codigo.\n";
        return;
    }
    cout << "Codigo del paciente: ";
    getline(cin >> ws, c.codPaciente);
    if (buscarPaciente(c.codPaciente).codigo == "") {
        cout << "Error: el paciente no existe.\n";
        return;
    }
    cout << "Codigo del medico: ";
    getline(cin >> ws, c.codMedico);
    if (buscarMedico(c.codMedico).codigo == "") {
        cout << "Error: el medico no existe.\n";
        return;
    }
    cout << "Fecha (dd/mm/aaaa): ";
    getline(cin >> ws, c.fecha);
    cout << "Hora (hh:mm): ";
    getline(cin >> ws, c.hora);
    if (horarioOcupado(c.codMedico, c.fecha, c.hora)) {
        cout << "Error: el medico ya tiene una cita en ese horario.\n";
        return;
    }
    c.estado = "Programada";

    fstream archivo;
    archivo.open(ARCH_CITAS, ios::out | ios::app);
    escribirCita(archivo, c);
    archivo.close();
    cout << "Cita registrada!\n";
}

// Reescribe citas.txt con un archivo temporal (igual que procesarPedido)
void actualizarEstadoCita(string codBuscado, string nuevoEstado) {
    fstream origen, temporal;
    string nombreTemp = "citas_tmp.txt";

    origen.open(ARCH_CITAS, ios::in);
    temporal.open(nombreTemp, ios::out);
    Cita c;
    while (origen && leerCita(origen, c)) {
        if (c.codigo == codBuscado)
            c.estado = nuevoEstado;
        escribirCita(temporal, c);
    }
    origen.close();
    temporal.close();
    remove(ARCH_CITAS.c_str());
    rename(nombreTemp.c_str(), ARCH_CITAS.c_str());
}

void registrarAtencion() {
    Atencion a;
    cout << "Codigo de la cita: ";
    getline(cin >> ws, a.codCita);
    Cita c = buscarCita(a.codCita);
    if (c.codigo == "") {
        cout << "Error: la cita no existe.\n";
        return;
    }
    if (c.estado != "Programada") {
        cout << "Error: solo se puede atender una cita Programada.\n";
        return;
    }
    cout << "Paciente: " << buscarPaciente(c.codPaciente).nombre << endl;
    cout << "Diagnostico: ";
    getline(cin >> ws, a.diagnostico);
    cout << "Costo de atencion (S/): ";
    cin >> a.costo;

    fstream archivo;
    archivo.open(ARCH_ATENCIONES, ios::out | ios::app);
    escribirAtencion(archivo, a);
    archivo.close();
    actualizarEstadoCita(a.codCita, "Atendida");
    cout << "Atencion registrada! La cita paso a Atendida.\n";
}

void registrarPago() {
    Pago p;
    cout << "Codigo de la cita: ";
    getline(cin >> ws, p.codCita);
    Atencion a = buscarAtencion(p.codCita);
    if (a.codCita == "") {
        cout << "Error: esa cita no tiene una atencion registrada.\n";
        return;
    }
    if (buscarPago(p.codCita).codCita != "") {
        cout << "Error: esa cita ya fue pagada.\n";
        return;
    }
    cout << fixed << setprecision(2);
    cout << "Consulta: S/ " << a.costo << endl;
    cout << "Pago recibido (S/): ";
    cin >> p.monto;
    if (p.monto < a.costo) {
        cout << "Error: el pago no cubre el costo. Pago cancelado.\n";
        return;
    }
    p.estado = "Pagado";

    fstream archivo;
    archivo.open(ARCH_PAGOS, ios::out | ios::app);
    escribirPago(archivo, p);
    archivo.close();
    cout << "Pago registrado! Estado: Pagado\n";
}

// ===============================================================
// CONSULTAS
// ===============================================================

void mostrarPacienteCodigoODni(string dato) {
    Paciente p = buscarPaciente(dato);
    if (p.codigo == "") {
        cout << "No se encontro el paciente.\n";
        return;
    }
    cout << "\nPaciente encontrado:\n";
    cout << "Codigo   : " << p.codigo   << endl;
    cout << "DNI      : " << p.dni      << endl;
    cout << "Nombre   : " << p.nombre   << endl;
    cout << "Edad     : " << p.edad     << endl;
    cout << "Sexo     : " << p.sexo     << endl;
    cout << "Telefono : " << p.telefono << endl;
    cout << "Estado   : " << p.estado   << endl;
}

void mostrarMedicoPorCodigo(string codBuscado) {
    Medico m = buscarMedico(codBuscado);
    if (m.codigo == "") {
        cout << "No se encontro el medico.\n";
        return;
    }
    cout << "\nMedico encontrado:\n";
    cout << "Codigo       : " << m.codigo       << endl;
    cout << "Nombre       : " << m.nombre       << endl;
    cout << "Especialidad : " << m.especialidad << endl;
    cout << "Consultorio  : " << m.consultorio  << endl;
    cout << "Estado       : " << m.estado       << endl;
}

void mostrarCitaPorCodigo(string codBuscado) {
    Cita c = buscarCita(codBuscado);
    if (c.codigo == "") {
        cout << "No se encontro la cita.\n";
        return;
    }
    cout << "\nCita encontrada:\n";
    cout << "Codigo   : " << c.codigo << endl;
    cout << "Paciente : " << c.codPaciente << " - " << buscarPaciente(c.codPaciente).nombre << endl;
    cout << "Medico   : " << c.codMedico   << " - " << buscarMedico(c.codMedico).nombre << endl;
    cout << "Fecha    : " << c.fecha << endl;
    cout << "Hora     : " << c.hora  << endl;
    cout << "Estado   : " << c.estado << endl;
}

void mostrarCitasPorEstado(string estado) {
    fstream archivo;
    archivo.open(ARCH_CITAS, ios::in);
    if (!archivo) {
        cerr << "No hay citas registradas.\n";
        return;
    }
    Cita c;
    int contador = 0;

    cout << left << setw(8)  << "Cita"  << setw(20) << "Paciente"
                 << setw(20) << "Medico" << setw(12) << "Fecha"
                 << setw(7)  << "Hora"  << setw(11) << "Estado" << "\n";
    cout << string(78, '-') << "\n";

    while (leerCita(archivo, c)) {
        if (c.estado == estado) {
            string nomPac = buscarPaciente(c.codPaciente).nombre;
            string nomMed = buscarMedico(c.codMedico).nombre;
            cout << left << setw(8)  << c.codigo << setw(20) << nomPac
                         << setw(20) << nomMed   << setw(12) << c.fecha
                         << setw(7)  << c.hora   << setw(11) << c.estado << "\n";
            contador++;
        }
    }
    archivo.close();
    if (contador == 0) cout << "No hay citas " << estado << "s.\n";
}

void consultas() {
    int opcion;
    string dato, codBuscado;
    cout << "--- CONSULTAS ---\n";
    cout << "1) Buscar paciente\n2) Buscar medico\n3) Buscar cita\n";
    cout << "4) Citas pendientes\n5) Citas atendidas\nOpcion: ";
    cin >> opcion;
    switch (opcion) {
        case 1:
            cout << "Codigo o DNI del paciente: ";
            getline(cin >> ws, dato);
            mostrarPacienteCodigoODni(dato);
            break;
        case 2:
            cout << "Codigo del medico: ";
            getline(cin >> ws, codBuscado);
            mostrarMedicoPorCodigo(codBuscado);
            break;
        case 3:
            cout << "Codigo de la cita: ";
            getline(cin >> ws, codBuscado);
            mostrarCitaPorCodigo(codBuscado);
            break;
        case 4: 
            mostrarCitasPorEstado("Programada"); break;
        case 5:
            mostrarCitasPorEstado("Atendida");   break;
        default: 
            cout << "Opcion no valida.\n";
    }
}

// ===============================================================
// REPORTES
// ===============================================================

int contarRegistros(string nombreArchivo) {
    fstream archivo;
    archivo.open(nombreArchivo, ios::in);
    if (!archivo) {
        cerr << "Archivo no encontrado";
    }

    string linea;
    int contador = 0;
    while (getline(archivo, linea))
        if (linea != "") contador++;
    archivo.close();
    return contador;
}

bool tieneCitaAtendida(string codPaciente) {
    fstream archivo;
    archivo.open(ARCH_CITAS, ios::in);
    if (!archivo) {
        archivo.close();
        return false;
    }

    Cita c;
    while (leerCita(archivo, c)) {
        if (c.codPaciente == codPaciente && c.estado == "Atendida") {
            archivo.close();
            return true;
        }
    }
    archivo.close();
    return false;
}

void reportes() {
    Cita c;
    Medico m;
    Atencion a;
    Pago pg;
    Paciente p;
    fstream archivo, archivo2;

    // REPORTE 1 y 2
    cout << "REPORTE 1 - Total pacientes: " << contarRegistros(ARCH_PACIENTES) << endl;
    cout << "REPORTE 2 - Total medicos: "   << contarRegistros(ARCH_MEDICOS)   << endl;

    // REPORTE 3: citas programadas
    int programadas = 0;
    archivo.open(ARCH_CITAS, ios::in);

    while (archivo && leerCita(archivo, c))
        if (c.estado == "Programada") programadas++;
    archivo.close();
    cout << "REPORTE 3 - Total citas programadas: " << programadas << endl;

    // REPORTE 4: medico con mas atenciones
    string mejorMedico = "(ninguno)";
    int mayor = 0;
    
    while (leerMedico(archivo, m)) {
        int cantidad = 0;
        fstream archivo2;                       // se abre de nuevo para cada medico
        archivo2.open(ARCH_ATENCIONES, ios::in);
        while (archivo2 && leerAtencion(archivo2, a))
            if (buscarCita(a.codCita).codMedico == m.codigo) cantidad++;
        archivo2.close();

        if (cantidad > mayor) {
            mayor = cantidad;
            mejorMedico = m.nombre;
        }
    }
    archivo.close();
    cout << "Medico con mas atenciones: " << mejorMedico << " (" << mayor << ")" << endl;

    // REPORTE 5: especialidad mas solicitada
    int contador[5] = {0, 0, 0, 0, 0};
    archivo.open(ARCH_CITAS, ios::in);

    while (archivo && leerCita(archivo, c)) {
        string esp = buscarMedico(c.codMedico).especialidad;
        for (int i = 0; i < 5; i++)
            if (esp == ESPECIALIDADES[i]) contador[i]++;
    }
    archivo.close();
    int pos = 0;
    for (int i = 1; i < 5; i++)
        if (contador[i] > contador[pos]) pos = i;
    cout << "REPORTE 5 - Especialidad mas solicitada: ";
    if (contador[pos] == 0) cout << "(sin citas)" << endl;
    else cout << ESPECIALIDADES[pos] << " (" << contador[pos] << " citas)" << endl;

    // REPORTE 6: pacientes atendidos
    cout << "REPORTE 6 - Pacientes atendidos:\n";
    int atendidos = 0;
    archivo.open(ARCH_PACIENTES, ios::in);

    while (archivo && leerPaciente(archivo, p)) {
        if (tieneCitaAtendida(p.codigo)) {
            cout << "   - " << p.nombre << endl;
            atendidos++;
        }
    }
    archivo.close();
    if (atendidos == 0) cout << "   (ninguno)\n";

    // REPORTE 7: ingresos totales
    double total = 0;
    archivo.open(ARCH_PAGOS, ios::in);
    while (archivo && leerPago(archivo, pg))
        total += pg.monto;
    archivo.close();
    cout << "REPORTE 7 - Ingresos totales: S/ " << fixed << setprecision(2) << total << endl;
}

// ===============================================================
// GUARDAR / CARGAR DATOS (copia de respaldo .bak de cada archivo)
// ===============================================================

bool copiarArchivo(string origen, string destino) {
    ifstream in(origen);
    if (!in) return false;
    ofstream out(destino);
    out << in.rdbuf();
    return true;
}

void guardarDatos() {
    for (int i = 0; i < 5; i++)
        copiarArchivo(ARCHIVOS[i], ARCHIVOS[i] + ".bak");
    cout << "Datos guardados en archivos de respaldo (.bak).\n";
}

void cargarDatos() {
    int cargados = 0;
    for (int i = 0; i < 5; i++)
        if (copiarArchivo(ARCHIVOS[i] + ".bak", ARCHIVOS[i])) cargados++;
    if (cargados == 0) cout << "No hay respaldo para cargar. Use primero la opcion 10.\n";
    else cout << "Datos cargados desde el respaldo (" << cargados << " archivos).\n";
}

// ===============================================================
// SISTEMA
// ===============================================================
void sistema() {
    int opcion;

    while (true) {
        opcion = menu();
        if (opcion == 0) break;
        switch (opcion) {
            case 1:  registrarPaciente(); break;
            case 2:  listarPacientes();  break;
            case 3:  registrarMedico();   break;
            case 4:  listarMedicos();    break;
            case 5:  registrarCita();     break;
            case 6:  registrarAtencion(); break;
            case 7:  registrarPago();     break;
            case 8:  consultas();         break;
            case 9:  reportes();          break;
            case 10: guardarDatos();      break;
            case 11: cargarDatos();       break;
            default: cout << "Opcion no valida.\n";
        }
        cout << "Presione cualquier tecla para continuar...." << endl;
        getch();
        cout << "\033[2J\033[1;1H";
    }
}
